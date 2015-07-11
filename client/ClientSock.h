#if !defined(AFX_CLIENTSOCK_H__81FF86E3_B94C_4FB7_BE87_EA0C27430C05__INCLUDED_)
#define AFX_CLIENTSOCK_H__81FF86E3_B94C_4FB7_BE87_EA0C27430C05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSock.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSock command target
class CChessBorad;

class CClientSock : public CSocket
{
// Attributes
public:

// Operations
public:
	CClientSock();
	virtual ~CClientSock();

// Overrides
public:
	void AttachDlg(CDialog *pDlg);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSock)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CChessBorad *m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCK_H__81FF86E3_B94C_4FB7_BE87_EA0C27430C05__INCLUDED_)
