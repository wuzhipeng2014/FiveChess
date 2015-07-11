#if !defined(AFX_SRVINFO_H__66656ECC_1EB4_499E_9D5F_F11E1EBFACD0__INCLUDED_)
#define AFX_SRVINFO_H__66656ECC_1EB4_499E_9D5F_F11E1EBFACD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SrvInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSrvInfo dialog

class CSrvInfo : public CDialog
{
// Construction
public:
	CSrvInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSrvInfo)
	enum { IDD = IDD_SRVINFO_DIALOG };
	UINT	m_Port;
	CString	m_IP;
	CString	m_NickName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrvInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSrvInfo)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVINFO_H__66656ECC_1EB4_499E_9D5F_F11E1EBFACD0__INCLUDED_)
