#if !defined(AFX_LEFTPANEL_H__93E4EF28_7B82_4CFA_AB8C_974A2C0FF223__INCLUDED_)
#define AFX_LEFTPANEL_H__93E4EF28_7B82_4CFA_AB8C_974A2C0FF223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeftPanel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeftPanel dialog

class CLeftPanel : public CDialog
{
// Construction
public:
	CLeftPanel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLeftPanel)
	enum { IDD = IDD_LEFTPANEL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftPanel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLeftPanel)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBegingame();
	afx_msg void OnBtBack();
	afx_msg void OnDrawChess();
	afx_msg void OnGiveUp();
	afx_msg void OnBackPlay();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTPANEL_H__93E4EF28_7B82_4CFA_AB8C_974A2C0FF223__INCLUDED_)
