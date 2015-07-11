#if !defined(AFX_BLACKSTATIC_H__5D907225_402F_47BB_93C5_8C75602F0D28__INCLUDED_)
#define AFX_BLACKSTATIC_H__5D907225_402F_47BB_93C5_8C75602F0D28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlackStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBlackStatic window

class CBlackStatic : public CStatic
{
// Construction
public:
	CBlackStatic();
	BOOL m_bDrawFrame;	//ÊÇ·ñ»æÖÆ±ß¿ò
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlackStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetWindowText(LPCTSTR lpText);
	virtual ~CBlackStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBlackStatic)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLACKSTATIC_H__5D907225_402F_47BB_93C5_8C75602F0D28__INCLUDED_)
