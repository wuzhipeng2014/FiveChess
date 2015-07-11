// SrvInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ClientFiveChess.h"
#include "SrvInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSrvInfo dialog

CSrvInfo::CSrvInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CSrvInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSrvInfo)
	m_Port = 0;
	m_IP = _T("");
	m_NickName = _T("");
	//}}AFX_DATA_INIT
}

void CSrvInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSrvInfo)
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDV_MinMaxUInt(pDX, m_Port, 0, 10000);
	DDX_Text(pDX, IDC_SVRIP, m_IP);
	DDX_Text(pDX, IDC_NICKNAME, m_NickName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSrvInfo, CDialog)
	//{{AFX_MSG_MAP(CSrvInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSrvInfo message handlers
void CSrvInfo::OnOK() 
{
	UpdateData();
	CDialog::OnOK();
}
