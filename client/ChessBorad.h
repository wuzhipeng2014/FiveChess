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


/************************ö�ٳ���˵��****************************
CT_BEGINGAME			��ʼ��Ϸ
CT_NETTEST				�������
CT_POINT				��������
CT_TEXT					�ı���Ϣ
CT_WINPOINT				Ӯ��ʱ�������յ�����
CT_BACKREQUEST			��������
CT_BACKACCEPTANCE		ͬ�����
CT_BACKDENY				�ܾ�����
CT_DRAWCHESSREQUEST		��������
CT_DRAWCHESSACCEPTANCE	ͬ�����
CT_DRAWCHESSDENY		�ܾ�����
CT_GIVEUP				����
***************************************************************/
enum  CMDTYPE	{ CT_BEGINGAME,CT_NETTEST,CT_POINT,CT_TEXT,CT_WINPOINT,
					CT_BACKREQUEST,CT_BACKACCEPTANCE,CT_BACKDENY,CT_DRAWCHESSREQUEST,
					CT_DRAWCHESSACCEPTANCE,CT_DRAWCHESSDENY,CT_GIVEUP
				};
//�������ݱ��ṹ
struct TCP_PACKAGE
{
	CMDTYPE cmdType;	//��������
	CPoint  chessPT;	//����������(�к�������)
	CPoint  winPT[2];	//Ӯ��ʱ��·��(�����յ�)
	char chText[512];	//�ı�����
};


//����ڵ���ɫ
typedef enum NODECOLOR{ ncWHITE,ncBLACK,ncUNKOWN};

//����ڵ���
class NODE
{
public:
	NODECOLOR  m_Color;       //������ɫ
	CPoint     m_Point;       //���������
	int        m_nX;			//����
	int        m_nY;			//����
public:
	NODE*      m_pRecents[8]; //�ٽ�����

	BOOL       m_IsUsed;      //�����Ƿ���
	NODE()
	{
		m_Color = ncUNKOWN;
		m_IsUsed=FALSE;
	}
	~NODE()
	{ 

	}
} ;
//��Ϸ״̬
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

	int m_nRowCount,m_nColCount;		//�������
	int m_nCellWidth,m_nCellHeight;		//����Ⱥ͸߶�
	int m_nOrginX,m_nOrginY;			//������
	int m_nBmpWidth,m_nBmpHeight;		//λͼ�Ŀ�Ⱥ͸߶�


	NODE m_NodeList[11][11];	//��������
	CPoint  m_Startpt;			//��Ӯ��ʱ��¼��ʼ�������,Ŀ������Ӯ��ʱ��������
	CPoint  m_Endpt;			//������ʱ��¼�����������
	BOOL m_IsWin;				//�ж��Ƿ�Ӯ����
	BOOL m_IsDown;				//�ж��û��Ƿ���Է�������
	BOOL m_IsStart;				//��Ϸ�Ƿ�ʼ
	BOOL m_IsConnect;			//�Ƿ����ӷ�����
	GameState m_State;		
	CString  m_csNickName;		//�ǳ�

	CClientSock m_ClientSock;	//�ͻ����׽���
	int m_TestNum;				//����״̬����				


	double m_fRateX,m_fRateY;	//�����ڴ�С�ı�ʱͼ������ű���
	CPoint m_LocalChessPT;		//��¼�����û�������õ���������(�߼�����)
	CPoint m_RemoteChessPT;		//��¼�Է�������õ���������(�߼�����)

	CPtrList m_BackPlayList;	//��¼�û�����Ĳ���
	BOOL m_bBackPlay;			//�Ƿ������Ϸ�ط�

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
