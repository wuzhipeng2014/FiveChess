// ClientFiveChessDlg.h : header file
//

#if !defined(AFX_CLIENTFIVECHESSDLG_H__4089BD5D_D02A_4B5E_9661_A1DE3691570D__INCLUDED_)
#define AFX_CLIENTFIVECHESSDLG_H__4089BD5D_D02A_4B5E_9661_A1DE3691570D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientSock.h"
#include "RightPanel.h"
#include "LeftPanel.h"
#include "ChessBorad.h"

/////////////////////////////////////////////////////////////////////////////
// CClientFiveChessDlg dialog


class CClientFiveChessDlg : public CDialog
{
// Construction
public:
	void OnCancel();
	CClientFiveChessDlg(CWnd* pParent = NULL);	// standard constructor

	void OnBegin() ;

	
	CLeftPanel  m_LeftPanel;	//左边的列表信息窗口
	CRightPanel m_RightPanel;	//右边的列表信息窗口
	CChessBorad m_ChessBoard;	//棋盘窗口
	BOOL m_bCreatePanel;		//是否创建了列表信息窗口


// Dialog Data
	//{{AFX_DATA(CClientFiveChessDlg)
	enum { IDD = IDD_CLIENTFIVECHESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientFiveChessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientFiveChessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTFIVECHESSDLG_H__4089BD5D_D02A_4B5E_9661_A1DE3691570D__INCLUDED_)
