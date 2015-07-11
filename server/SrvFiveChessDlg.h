// SrvFiveChessDlg.h : header file
//

#if !defined(AFX_SRVFIVECHESSDLG_H__4D538841_DAB4_41A6_B7E2_3A884F463028__INCLUDED_)
#define AFX_SRVFIVECHESSDLG_H__4D538841_DAB4_41A6_B7E2_3A884F463028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSrvFiveChessDlg dialog
#include "CustomMenu.h"
#include "SrvSock.h"
#include "ClientSock.h"


#include "RightPanel.h"
#include "LeftPanel.h"
#include "ChessBorad.h"

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

class CSrvFiveChessDlg : public CDialog
{

// Construction
public:
	void OnCancel();

	CLeftPanel  m_LeftPanel;	//游戏控制窗口
	CRightPanel m_RightPanel;	//对方信息窗口
	CChessBorad m_ChessBoard;	//棋盘窗口
	BOOL m_bCreatePanel;		//是否创建了列表信息窗口
	BOOL m_IsStart;

	void Start();
	void AcceptConnection();
	CSrvFiveChessDlg(CWnd* pParent = NULL);	// standard constructor

	CCustomMenu m_Menu;



	BOOL m_IsConnect;
// Dialog Data
	//{{AFX_DATA(CSrvFiveChessDlg)
	enum { IDD = IDD_SRVFIVECHESS_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrvFiveChessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSrvFiveChessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnMenuSvrSetting();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenuidmAboutbox();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVFIVECHESSDLG_H__4D538841_DAB4_41A6_B7E2_3A884F463028__INCLUDED_)
