// ClientFiveChessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientFiveChess.h"
#include "ClientFiveChessDlg.h"
#include "SrvInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About




class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientFiveChessDlg dialog

CClientFiveChessDlg::CClientFiveChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientFiveChessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientFiveChessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINICON);



	m_bCreatePanel = FALSE;
}

void CClientFiveChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientFiveChessDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientFiveChessDlg, CDialog)
	//{{AFX_MSG_MAP(CClientFiveChessDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientFiveChessDlg message handlers

BOOL CClientFiveChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	AfxInitRichEdit();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon




	//创建窗口列表
	m_RightPanel.Create(IDD_RIGHTPANEL_DIALOG,this);
	m_RightPanel.ShowWindow(SW_SHOW);

	CRect wndRC;
	m_RightPanel.GetWindowRect(wndRC);
	int nWidth = wndRC.Width();
	
	CRect cltRC;	//客户区域
	GetClientRect(cltRC);
	int nHeight = cltRC.Height();
	
	//定义窗口列表显示的区域
	CRect pnlRC;
	pnlRC.left = cltRC.right-nWidth;
	pnlRC.top = 0;
	pnlRC.bottom = nHeight;
	pnlRC.right = cltRC.right;
	//显示窗口
	m_RightPanel.MoveWindow(pnlRC);

	//记录右边窗口的宽度
	int nRightWidth = nWidth;

	//创建左边的列表信息窗口
	m_LeftPanel.Create(IDD_LEFTPANEL_DIALOG,this);
	m_LeftPanel.ShowWindow(SW_SHOW);

	m_LeftPanel.GetWindowRect(wndRC);
	nWidth = wndRC.Width();

	pnlRC.left = 0;
	pnlRC.top = 0;
	pnlRC.bottom = nHeight;
	pnlRC.right = nWidth;
	
	//记录左边窗口的宽度
	int nLeftWidth = nWidth;
	//显示窗口
	m_LeftPanel.MoveWindow(pnlRC);

	//创建棋盘窗口
	m_ChessBoard.Create(IDD_CHESSBORAD_DIALOG,this);
	m_ChessBoard.ShowWindow(SW_SHOW);
	//计算棋盘的显示区域

	pnlRC.left = nLeftWidth;	//为左边窗口的宽度
	pnlRC.top = 0;
	pnlRC.bottom = nHeight;		//主窗口的高度
	pnlRC.right = cltRC.Width() - nRightWidth;	//整个窗口的区域去除右边窗口的宽度
	
	m_ChessBoard.MoveWindow(pnlRC);
	
	m_bCreatePanel = TRUE;
	return TRUE; 
}

void CClientFiveChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientFiveChessDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
/*

	CDC* pDC = GetDC();
	CBitmap bmp,bmp2,bk;
	CDC memdc;
	memdc.CreateCompatibleDC(pDC);
	bmp.LoadBitmap(IDB_BLACK);
	bmp2.LoadBitmap(IDB_WHITE);
	bk.LoadBitmap(IDB_CHESSBOARD);
	memdc.SelectObject(&bk);
	pDC->BitBlt(0,0,600,600,&memdc,0,0,SRCCOPY);
	
	if (m_IsWin)
	{
		CPen pen(PS_SOLID,2,RGB(255,0,0));
		pDC->SelectObject(&pen);
		pDC->MoveTo(m_Startpt);
		pDC->LineTo(m_Endpt);
	}
	for (int m=0; m<row+1; m++)
		for (int n=0; n<col+1; n++)
		{
			if (m_NodeList[m][n].m_Color == ncWHITE)
			{
				memdc.SelectObject(&bmp);
				pDC->BitBlt(m_NodeList[m][n].m_Point.x-11,m_NodeList[m][n].m_Point.y-11,22,22,&memdc,0,0,SRCCOPY);	
			}
			else if (m_NodeList[m][n].m_Color == ncBLACK)
			{
				memdc.SelectObject(&bmp2);
				pDC->BitBlt(m_NodeList[m][n].m_Point.x-11 ,m_NodeList[m][n].m_Point.y-11,22,22,&memdc,0,0,SRCCOPY);				
			}
		}
	bmp.DeleteObject();
	ReleaseDC(&memdc);
	DrawChessboard();
*/


}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientFiveChessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientFiveChessDlg::OnOK() 
{
	
	
}

void CClientFiveChessDlg::OnBegin() 
{
	m_ChessBoard.BeginGame();
}

void CClientFiveChessDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if (m_bCreatePanel)
	{
		CRect wndRC;
		m_RightPanel.GetWindowRect(wndRC);
		int nWidth = wndRC.Width();
		
		CRect cltRC;	//客户区域
		GetClientRect(cltRC);
		int nHeight = cltRC.Height();
		
		//定义窗口列表显示的区域
		CRect pnlRC;
		pnlRC.left = cltRC.right-nWidth;
		pnlRC.top = 0;
		pnlRC.bottom = nHeight;
		pnlRC.right = cltRC.right;
		//显示窗口
		m_RightPanel.MoveWindow(pnlRC);
		int nRightWidth = nWidth;
		m_RightPanel.Invalidate();

		//显示左边的窗口列表区域
		m_LeftPanel.GetWindowRect(wndRC);
		nWidth = wndRC.Width();

		pnlRC.left = 0;
		pnlRC.top = 0;
		pnlRC.bottom = nHeight;
		pnlRC.right = nWidth;
		//显示窗口
		m_LeftPanel.MoveWindow(pnlRC);
		int nLeftWidth = nWidth;

		pnlRC.left = nLeftWidth;					//为左边窗口的宽度
		pnlRC.top = 0;
		pnlRC.bottom = nHeight;						//主窗口的高度
		pnlRC.right = cltRC.Width() - nRightWidth;	//整个窗口的区域去除右边窗口的宽度
		m_ChessBoard.MoveWindow(pnlRC);
		m_ChessBoard.Invalidate();
		
	}
}

void CClientFiveChessDlg::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CDialog::OnWindowPosChanged(lpwndpos);
	if (m_bCreatePanel)
	{
		m_ChessBoard.Invalidate();
		m_RightPanel.Invalidate();
	}
}

void CClientFiveChessDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	lpMMI->ptMinTrackSize.x = 800;
	lpMMI->ptMinTrackSize.y = 500;	
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CClientFiveChessDlg::OnCancel()
{
	m_ChessBoard.FreeBackPlayList();
	CDialog::OnCancel();
}
