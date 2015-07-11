// BlackStatic.cpp : implementation file
//

#include "stdafx.h"
#include "clientfivechess.h"
#include "BlackStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBlackStatic

CBlackStatic::CBlackStatic()
{
	m_bDrawFrame = TRUE;
}

CBlackStatic::~CBlackStatic()
{
}


BEGIN_MESSAGE_MAP(CBlackStatic, CStatic)
	//{{AFX_MSG_MAP(CBlackStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBlackStatic message handlers

void CBlackStatic::OnPaint() 
{
	CRect cltRC;
	GetClientRect(cltRC);
	CPaintDC dc(this); // device context for painting
	if (m_bDrawFrame)	//»æÖÆ±ß¿ò
	{
		CRect wndRC;
		GetWindowRect(wndRC);
		ScreenToClient(wndRC);
		CDC* pDC = GetWindowDC();
		CBrush brush(RGB(0,0,0));
		pDC->FrameRect(wndRC,&brush);
	}
	else
	{
		CBrush bkBrush(RGB(247,227,199));
		dc.FillRect(cltRC,&bkBrush);
	}

	//»æÖÆ±³¾°ÑÕÉ«

	CString csText;
	GetWindowText(csText);
	CFont * pFont = GetFont();
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(pFont);

	dc.DrawText(csText,cltRC,DT_LEFT|DT_VCENTER);
	
	// Do not call CStatic::OnPaint() for painting messages
}

void CBlackStatic::SetWindowText(LPCTSTR lpText)
{
	CStatic::SetWindowText(lpText);
	Invalidate();
}
