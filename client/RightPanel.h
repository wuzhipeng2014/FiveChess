#if !defined(AFX_RIGHTPANEL_H__838736F6_E4C5_4AA8_B17A_CDBD05038DF5__INCLUDED_)
#define AFX_RIGHTPANEL_H__838736F6_E4C5_4AA8_B17A_CDBD05038DF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RightPanel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRightPanel dialog
#include "BlackStatic.h"

class CRightPanel : public CDialog
{
// Construction
public:
	void OnCancel();
	void OnOK();
	CRightPanel(CWnd* pParent = NULL);   // standard constructor
	CFont m_TextFont;
	CFont m_SendTextFont;	//发送文本的字体

	int m_nPanelToBottom;	
	int m_nEditToBottom;
	BOOL m_Initialized ;//对话框是否进行了初始化
// Dialog Data
	//{{AFX_DATA(CRightPanel)
	enum { IDD = IDD_RIGHTPANEL_DIALOG };
	CButton	m_SendBtn;
	CBlackStatic	m_Bottom;
	CBlackStatic	m_Top;
	CBlackStatic	m_Frame1;
	CRichEditCtrl	m_Msg;
	CBlackStatic	m_User;
	CBlackStatic	m_NetState;
	CRichEditCtrl	m_MsgList;
	CListCtrl	m_UserList;
	CBlackStatic	m_Panel3;
	CBlackStatic	m_Panel2;
	CBlackStatic	m_Panel1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRightPanel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRightPanel)
	virtual BOOL OnInitDialog();
	afx_msg void OnSendMsg();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTPANEL_H__838736F6_E4C5_4AA8_B17A_CDBD05038DF5__INCLUDED_)
