// Master.h : main header file for the MASTER DLL
//

#if !defined(AFX_MASTER_H__70011D62_BEA0_4622_A3A1_982B41D22A05__INCLUDED_)
#define AFX_MASTER_H__70011D62_BEA0_4622_A3A1_982B41D22A05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMasterApp
// See Master.cpp for the implementation of this class
//

class CMasterApp : public CWinApp
{
public:
	CMasterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMasterApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMasterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASTER_H__70011D62_BEA0_4622_A3A1_982B41D22A05__INCLUDED_)
