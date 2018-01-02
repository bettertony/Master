
#include "stdafx.h"
#include "hffix.hpp"
#include <sys/types.h>
#include <WinSock2.h>
 
#pragma comment(lib,"ws2_32.lib")

SOCKET HSocket = INVALID_SOCKET;

static int SeqNo = 1;

void InitNetwork()
{
  WSADATA wsa;
  WSAStartup(MAKEWORD(1,1),&wsa);
}

SOCKET ConnectSvr(const char* ServerAdddress,short ServerPort)
{
  HSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(HSocket<0)
  {
    printf("Create Socket faild errno:%d\n",GetLastError());
    return INVALID_SOCKET;
  }

  int nRxTimeout = 3 * 1000; 
  int iret = setsockopt(HSocket, SOL_SOCKET, SO_RCVTIMEO,reinterpret_cast<char *>(&nRxTimeout), sizeof(nRxTimeout));
  
  bool tcpNoDelay = true;
  iret = setsockopt(HSocket, IPPROTO_TCP, TCP_NODELAY,reinterpret_cast<char *>(&tcpNoDelay), sizeof(int) );

  int Zero = 65536;
  iret = setsockopt(HSocket, SOL_SOCKET, SO_RCVBUF,reinterpret_cast<char *>(&Zero), sizeof(int) );
  
  struct hostent* host = gethostbyname(ServerAdddress);
  if(host==NULL)
  {
    closesocket(HSocket);
    printf("gethostbyname %s faild errno:%d\n",ServerAdddress,GetLastError());
    return INVALID_SOCKET;
  }
  else
  {
    printf("Ip is [%u].[%u].[%u].[%u]\n",host->h_addr[0],host->h_addr[1],(unsigned char)host->h_addr[2],(unsigned char)host->h_addr[3]);
  }

  sockaddr_in serveraddr;
  memset((char *) &serveraddr,0,sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
    memcpy((char *)&serveraddr.sin_addr.s_addr,(char *)host->h_addr,host->h_length);
  serveraddr.sin_port = htons(ServerPort);

  if (connect(HSocket,(struct sockaddr *) &serveraddr,sizeof(serveraddr)) < 0)
  {
    printf("Connect %s %d Failed errno:%d\n",ServerAdddress,ServerPort,GetLastError());
    closesocket(HSocket);
    return INVALID_SOCKET;
  }
  else
  {
    printf("Connect %s %d Success\n",ServerAdddress,ServerPort);
  }

  return HSocket;
}

int DoHeartBeat()
{

}

int DoLogon()
{
  char buffer[8012];
  memset(buffer,0,sizeof(buffer));

  hffix::message_writer logon(buffer, sizeof(buffer));
  logon.push_back_header("FIX.4.4");
  logon.push_back_string(hffix::tag::MsgType, "A");
  logon.push_back_int(hffix::tag::EncryptMethod, 0);
  logon.push_back_int(hffix::tag::HeartBtInt, 30);
  logon.push_back_char(hffix::tag::ResetSeqNumFlag,'N');
  logon.push_back_string(hffix::tag::Username,"xiaoyunyu123");
  logon.push_back_string(hffix::tag::Password,"aa258758");
  logon.push_back_trailer();

  int iret = send(HSocket,(const char*)logon.message_begin(),logon.message_size(),0);
  if(iret<0)
  {
    printf("send logon request Failed errno:%d\n",GetLastError());
    closesocket(HSocket);
    return -1;
  }
  else
  {
    printf("send logon request success ,bodylength:%d\n",iret);
  }

  memset(buffer,0,sizeof(buffer));

  iret = recv(HSocket,buffer,sizeof(buffer),0);
  if(iret<=0)
  {
    printf("recv logon response Failed errno:%d iret:%d\n",GetLastError(),iret);
    closesocket(HSocket);
    return -1;
  }

  return 0;
}



int _tmain(int argc, _TCHAR* argv[])
{
  
  InitNetwork();

  HSocket = ConnectSvr("trade.lmaxtrader.com",443);

  if(HSocket<0)
  {
    return -1;
  }

  int iret = DoLogon();
  if(iret<0)
  {
    return -1;      
  }
  
  return 0;
}