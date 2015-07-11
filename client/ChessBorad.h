#if !defined(AFX_CHESSBORAD_H__516FE69D_CF30_48FE_8E7F_3DEA95E8660A__INCLUDED_)
#define AFX_CHESSBORAD_H__516FE69D_CF30_48FE_8E7F_3DEA95E8660A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChessBorad.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChessBorad dialog
#include "ClientSock.h"
#include "SrvInfo.h"


/************************枚举常量说明****************************
CT_BEGINGAME			开始游戏
CT_NETTEST				网络测试
CT_POINT				棋子坐标
CT_TEXT					文本信息
CT_WINPOINT				赢棋时的起点和终点棋子
CT_BACKREQUEST			悔棋请求
CT_BACKACCEPTANCE		同意悔棋
CT_BACKDENY				拒绝悔棋
CT_DRAWCHESSREQUEST		和棋请求
CT_DRAWCHESSACCEPTANCE	同意和棋
CT_DRAWCHESSDENY		拒绝和棋
CT_GIVEUP				认输
***************************************************************/
enum  CMDTYPE	{ CT_BEGINGAME,CT_NETTEST,CT_POINT,CT_TEXT,CT_WINPOINT,
					CT_BACKREQUEST,CT_BACKACCEPTANCE,CT_BACKDENY,CT_DRAWCHESSREQUEST,
					CT_DRAWCHESSACCEPTANCE,CT_DRAWCHESSDENY,CT_GIVEUP
				};
//定义数据报结构
struct TCP_PACKAGE
{
	CMDTYPE cmdType;	//命令类型
	CPoint  chessPT;	//五子棋坐标(行和列坐标)
	CPoint  winPT[2];	//赢棋时的路径(起点和终点)
	char chText[512];	//文本数据
};


//定义节点颜色
typedef enum NODECOLOR{ ncWHITE,ncBLACK,ncUNKOWN};

//定义节点类
class NODE
{
public:
	NODECOLOR  m_Color;       //棋子颜色
	CPoint     m_Point;       //棋子坐标点
	int        m_nX;			//索引
	int        m_nY;			//索引
public:
	NODE*      m_pRecents[8]; //临近棋子

	BOOL       m_IsUsed;      //棋子是否被用
	NODE()
	{
		m_Color = ncUNKOWN;
		m_IsUsed=FALSE;
	}
	~NODE()
	{ 

	}
} ;
//游戏状态
enum GameState {esBEGIN,esEND,esUNKNOWN};


class CChessBorad : public CDialog
{
// Construction
public:
	void GamePlayBack();
	void FreeBackPlayList();
	void InitBackPlayNode();
	void ReceiveData();
	void BeginGame();
	NODE* GetLikeNode(CPoint pt);
	NODE* IsWin(NODE* pCurrent);
	void InitializeNode();
	NODE* GetNodeFromPoint(CPoint pt);
	void SetRecentNode(NODE *pNode);
	void DrawChessboard();
	CChessBorad(CWnd* pParent = NULL);   // standard constructor

	int m_nRowCount,m_nColCount;		//表格行列
	int m_nCellWidth,m_nCellHeight;		//表格宽度和高度
	int m_nOrginX,m_nOrginY;			//表格起点
	int m_nBmpWidth,m_nBmpHeight;		//位图的宽度和高度


	NODE m_NodeList[11][11];	//棋子数组
	CPoint  m_Startpt;			//在赢棋时记录开始点的坐标,目的是在赢棋时绘制连线
	CPoint  m_Endpt;			//在输棋时记录结束点的坐标
	BOOL m_IsWin;				//判断是否赢或输
	BOOL m_IsDown;				//判断用户是否可以放置棋子
	BOOL m_IsStart;				//游戏是否开始
	BOOL m_IsConnect;			//是否连接服务器
	GameState m_State;		
	CString  m_csNickName;		//昵称

	CClientSock m_ClientSock;	//客户端套接字
	int m_TestNum;				//网络状态测试				


	double m_fRateX,m_fRateY;	//当窗口大小改变时图像的缩放比例
	CPoint m_LocalChessPT;		//记录本地用户最近放置的棋子坐标(逻辑坐标)
	CPoint m_RemoteChessPT;		//记录对方最近放置的棋子坐标(逻辑坐标)

	CPtrList m_BackPlayList;	//记录用户下棋的步骤
	BOOL m_bBackPlay;			//是否进行游戏回放

// Dialog Data
	//{{AFX_DATA(CChessBorad)
	enum { IDD = IDD_CHESSBORAD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChessBorad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChessBorad)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHESSBORAD_H__516FE69D_CF30_48FE_8E7F_3DEA95E8660A__INCLUDED_)
