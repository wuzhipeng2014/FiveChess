// ClientSock.cpp : implementation file
//

#include "stdafx.h"
#include "SrvFiveChess.h"
#include "ClientSock.h"
#include "SrvFiveChessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSock

CClientSock::CClientSock()
{
	m_pDlg = NULL;
}

CClientSock::~CClientSock()
{

}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSock, CSocket)
	//{{AFX_MSG_MAP(CClientSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSock member functions
void CClientSock::AttachDlg(CDialog *pDlg)
{
	m_pDlg = (CChessBorad*)pDlg;
}

void CClientSock::OnReceive(int nErrorCode) 
{
	if (m_pDlg != NULL)
		m_pDlg->ReceiveData();
	CSocket::OnReceive(nErrorCode);
}
