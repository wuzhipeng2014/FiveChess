// SrvSock.cpp : implementation file
//

#include "stdafx.h"
#include "SrvFiveChess.h"
#include "SrvSock.h"
#include "SrvFiveChessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSrvSock

CSrvSock::CSrvSock()
{
	m_pDlg = NULL;
}

CSrvSock::~CSrvSock()
{

}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSrvSock, CSocket)
	//{{AFX_MSG_MAP(CSrvSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSrvSock member functions

void CSrvSock::AttachDlg(CDialog *pDlg)
{
	m_pDlg = (CChessBorad*)pDlg;
}

void CSrvSock::OnAccept(int nErrorCode) 
{
	m_pDlg->AcceptConnection();	
	CSocket::OnAccept(nErrorCode);
}
