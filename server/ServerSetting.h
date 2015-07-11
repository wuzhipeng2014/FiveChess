#if !defined(AFX_SERVERSETTING_H__40CC9EF8_1547_4025_BB4F_67DCA41896BE__INCLUDED_)
#define AFX_SERVERSETTING_H__40CC9EF8_1547_4025_BB4F_67DCA41896BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServerSetting dialog

class CServerSetting : public CDialog
{
// Construction
public:
	CServerSetting(CWnd* pParent = NULL);   // standard constructor
	CString m_HostIP;
// Dialog Data
	//{{AFX_DATA(CServerSetting)
	enum { IDD = IDD_SERVERSETTING_DIALOG };

	CString	m_HostName;
	UINT	m_Port;
	CString	m_NickName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServerSetting)
	virtual void OnOK();
	afx_msg void OnSet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSETTING_H__40CC9EF8_1547_4025_BB4F_67DCA41896BE__INCLUDED_)
