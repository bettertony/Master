//+------------------------------------------------------------------+
#property copyright "Copyright 2018, Leyu intelligence Co.,Ltd."
#property version "1.1"

#import "Master.dll"
string Currency;
double FastAsk;
double FaskBid;
#import

extern double Lots=0.1;
extern bool   Compound=True;
extern double Spread=10;
//+------------------------------------------------------------------+
void OnTick()
  {
   int Tick;
   if(Compound==True)
     {
      Lots=(AccountEquity()/1000);
     }
   if(OrdersTotal()<1)
     {
      if(Currency==Symbol() && FastAsk+Spread<Ask)
        {
         Tick=OrderSend(Symbol(),OP_BUY,Lots,Ask,3,0,0,"Master",6,0,Green);
         if(Tick<=0) Print("Error: ",GetLastError());
         return;
        }
      if(Currency==Symbol() && FaskBid-Spread>Bid)
        {
         Tick=OrderSend(Symbol(),OP_SELL,Lots,Bid,3,0,0,"Master",9,0,Red);
         if(Tick<=0) Print("Error: ",GetLastError());
         return;
        }
     }
   for(int cnt=0;cnt<OrdersTotal();cnt++)
     {
      Tick=OrderSelect(0,SELECT_BY_POS);
      if(OrderType()==OP_BUY)
        {
         Tick=OrderClose(OrderTicket(),OrderLots(),Bid,3,Green);
         if(Tick<=0) Print("Error: ",GetLastError());
         return;
        }
      if(OrderType()==OP_SELL)
        {
         Tick=OrderClose(OrderTicket(),OrderLots(),Ask,3,Red);
         if(Tick<=0) Print("Error: ",GetLastError());
         return;
        }
     }
   return;
  }

