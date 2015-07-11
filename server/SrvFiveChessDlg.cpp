// SrvFiveChessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SrvFiveChess.h"
#include "SrvFiveChessDlg.h"
#include "ServerSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About



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
// CSrvFiveChessDlg dialog

CSrvFiveChessDlg::CSrvFiveChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSrvFiveChessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSrvFiveChessDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINICON);

	m_bCreatePanel = FALSE;

}

void CSrvFiveChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSrvFiveChessDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSrvFiveChessDlg, CDialog)
	//{{AFX_MSG_MAP(CSrvFiveChessDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_COMMAND(ID_MENUSVRSETTING, OnMenuSvrSetting)
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MENUIDM_ABOUTBOX, OnMenuidmAboutbox)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSrvFiveChessDlg message handlers

BOOL CSrvFiveChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization her

	HMENU hMenu = GetMenu()->GetSafeHmenu();
	if (hMenu != NULL)
	{
		m_Menu.AttatchMenu(hMenu);
		m_Menu.SetMenuItemInfo(&m_Menu);
	}

	AfxInitRichEdit();
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

void CSrvFiveChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSrvFiveChessDlg::OnPaint() 
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

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSrvFiveChessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSrvFiveChessDlg::OnOK() 
{

}

void CSrvFiveChessDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	m_Menu.DrawItem(lpDrawItemStruct);	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CSrvFiveChessDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	m_Menu.MeasureItem(lpMeasureItemStruct);
	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CSrvFiveChessDlg::AcceptConnection()
{

}

void CSrvFiveChessDlg::OnMenuSvrSetting() 
{
	m_ChessBoard.OnMenuSvrSetting();
}






void CSrvFiveChessDlg::Start()
{
	if (m_IsStart == FALSE)
	{
		m_IsStart = TRUE;
//		InitializeNode();
	}
}

void CSrvFiveChessDlg::OnTimer(UINT nIDEvent) 
{

	CDialog::OnTimer(nIDEvent);
}

void CSrvFiveChessDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{

	CDialog::OnLButtonUp(nFlags, point);
}

void CSrvFiveChessDlg::OnMenuidmAboutbox() 
{
	CAboutDlg AboutDlg;
	AboutDlg.DoModal();
}

void CSrvFiveChessDlg::OnSize(UINT nType, int cx, int cy) 
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
		m_LeftPanel.Invalidate();
		int nLeftWidth = nWidth;

		pnlRC.left = nLeftWidth;	//为左边窗口的宽度
		pnlRC.top = 0;
		pnlRC.bottom = nHeight;	//主窗口的高度
		pnlRC.right = cltRC.Width() - nRightWidth;	//整个窗口的区域去除右边窗口的宽度

		m_ChessBoard.MoveWindow(pnlRC);
		m_ChessBoard.Invalidate();
	}	
}

void CSrvFiveChessDlg::OnCancel()
{
	m_ChessBoard.FreeBackPlayList();	
	CDialog::OnCancel();
}

void CSrvFiveChessDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	lpMMI->ptMinTrackSize.x = 800;
	lpMMI->ptMinTrackSize.y = 500;
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CSrvFiveChessDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	OnSize(0, 0, 0);	
}
