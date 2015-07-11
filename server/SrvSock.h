#if !defined(AFX_SRVSOCK_H__B7975ACF_987E_4DE4_9B3A_C9BDC22C1890__INCLUDED_)
#define AFX_SRVSOCK_H__B7975ACF_987E_4DE4_9B3A_C9BDC22C1890__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SrvSock.h : header file
//




/////////////////////////////////////////////////////////////////////////////
// CSrvSock command target
class CChessBorad;

class CSrvSock : public CSocket
{
// Attributes
public:

// Operations
public:
	CSrvSock();
	virtual ~CSrvSock();

// Overrides
public:
	void AttachDlg(CDialog* pDlg);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSrvSock)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSrvSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CChessBorad *m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVSOCK_H__B7975ACF_987E_4DE4_9B3A_C9BDC22C1890__INCLUDED_)
