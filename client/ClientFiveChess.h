// ClientFiveChess.h : main header file for the CLIENTFIVECHESS application
//

#if !defined(AFX_CLIENTFIVECHESS_H__F8CA209E_0E68_4A09_A9DB_2469AD502381__INCLUDED_)
#define AFX_CLIENTFIVECHESS_H__F8CA209E_0E68_4A09_A9DB_2469AD502381__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientFiveChessApp:
// See ClientFiveChess.cpp for the implementation of this class
//

class CClientFiveChessApp : public CWinApp
{
public:
	CClientFiveChessApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientFiveChessApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientFiveChessApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTFIVECHESS_H__F8CA209E_0E68_4A09_A9DB_2469AD502381__INCLUDED_)
