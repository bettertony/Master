// Master.h : Master DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMasterApp
// �йش���ʵ�ֵ���Ϣ������� Master.cpp
//

class CMasterApp : public CWinApp
{
public:
	CMasterApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
