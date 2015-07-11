#if !defined(AFX_CUSTOMMENU_H__8BEA9350_FD68_43E6_8BA8_4D3E97D54E2E__INCLUDED_)
#define AFX_CUSTOMMENU_H__8BEA9350_FD68_43E6_8BA8_4D3E97D54E2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomMenu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomMenu window
//定义一个结构，记录菜单项的详细信息
struct CMenuItem
{
	CString	m_MenuText;		//菜单项的文本
	UINT	m_ImageIndex;	//菜单项图像索引
	int		m_MenuType;		//菜单项的类型，-2顶层菜单,-1弹出式菜单,0分隔条,其他普通菜单
};

class CCustomMenu : public CMenu
{
// Construction
public:
	CCustomMenu();
	int	m_ItemCount;			//记录菜单项的数量
	CMenuItem	*m_MenuList;	//记录每个菜单项的信息
	int m_Index;				//遍历菜单时使用的索引
	COLORREF m_BkColor;			//菜单背景颜色
	COLORREF m_SelTopColor;		//顶层菜单选中的颜色
	BOOL m_RandColor;			//菜单项是否启动随机颜色

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
	int GetTopMenuWidth();		//获取顶层菜单项的宽度		
	void DrawMenuBk(CDC* pDC,CRect Rect,COLORREF SrcColor,COLORREF DesColor, BOOL State= FALSE);
	void DrawSepMenu(CDC* pDC,CRect Rect);
	void DrawTopMenuBk(CDC* pDC,CRect Rect,BOOL State);
	void SetMenuItemText(CDC* pDC,LPSTR strMenuText,CRect Rect);
	BOOL SetMenuItemInfo(CMenu* pMenu,BOOL Toped = TRUE);
	static void GetAllItemCount(HMENU hMenu,int &ItemCount,BOOL FirstFind = TRUE);
	BOOL AttatchMenu(HMENU hMenu);
	virtual ~CCustomMenu();
	// Generated message map functions
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpStruct);		//设置菜单项大小
	virtual void DrawItem(LPDRAWITEMSTRUCT lpStruct);			//重绘菜单项
protected:
	//{{AFX_MSG(CCustomMenu)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMMENU_H__8BEA9350_FD68_43E6_8BA8_4D3E97D54E2E__INCLUDED_)
