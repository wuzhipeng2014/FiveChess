#if !defined(AFX_CUSTOMMENU_H__8BEA9350_FD68_43E6_8BA8_4D3E97D54E2E__INCLUDED_)
#define AFX_CUSTOMMENU_H__8BEA9350_FD68_43E6_8BA8_4D3E97D54E2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomMenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomMenu window
//����һ���ṹ����¼�˵������ϸ��Ϣ
struct CMenuItem
{
	CString	m_MenuText;		//�˵�����ı�
	UINT	m_ImageIndex;	//�˵���ͼ������
	int		m_MenuType;		//�˵�������ͣ�-2����˵�,-1����ʽ�˵�,0�ָ���,������ͨ�˵�
};

class CCustomMenu : public CMenu
{
// Construction
public:
	CCustomMenu();
	int	m_ItemCount;			//��¼�˵��������
	CMenuItem	*m_MenuList;	//��¼ÿ���˵������Ϣ
	int m_Index;				//�����˵�ʱʹ�õ�����
	COLORREF m_BkColor;			//�˵�������ɫ
	COLORREF m_SelTopColor;		//����˵�ѡ�е���ɫ
	BOOL m_RandColor;			//�˵����Ƿ����������ɫ

// Attributes
public:
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomMenu)
	//}}AFX_VIRTUAL
// Implementation
public:
	HRGN GetClientMenuRgn();
	int GetTopMenuWidth();		//��ȡ����˵���Ŀ��		
	void DrawMenuBk(CDC* pDC,CRect Rect,COLORREF SrcColor,COLORREF DesColor, BOOL State= FALSE);
	void DrawSepMenu(CDC* pDC,CRect Rect);
	void DrawTopMenuBk(CDC* pDC,CRect Rect,BOOL State);
	void SetMenuItemText(CDC* pDC,LPSTR strMenuText,CRect Rect);
	BOOL SetMenuItemInfo(CMenu* pMenu,BOOL Toped = TRUE);
	static void GetAllItemCount(HMENU hMenu,int &ItemCount,BOOL FirstFind = TRUE);
	BOOL AttatchMenu(HMENU hMenu);
	virtual ~CCustomMenu();
	// Generated message map functions
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpStruct);		//���ò˵����С
	virtual void DrawItem(LPDRAWITEMSTRUCT lpStruct);			//�ػ�˵���
protected:
	//{{AFX_MSG(CCustomMenu)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMMENU_H__8BEA9350_FD68_43E6_8BA8_4D3E97D54E2E__INCLUDED_)
