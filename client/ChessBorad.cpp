// ChessBorad.cpp : implementation file
//

#include "stdafx.h"
#include "clientfivechess.h"
#include "ChessBorad.h"
#include "ClientFiveChessDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChessBorad dialog


CChessBorad::CChessBorad(CWnd* pParent /*=NULL*/)
	: CDialog(CChessBorad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChessBorad)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_IsDown = TRUE;
	m_IsStart = FALSE;
	m_IsWin = FALSE;
	m_State = esUNKNOWN;
	m_IsConnect = FALSE;
	m_TestNum = 0;
	m_bBackPlay = FALSE;

	//加载棋盘位图
	CBitmap bmp;
	bmp.LoadBitmap(IDB_CHESSBOARD);
	
	//获取位图信息
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	m_nBmpWidth = bmpInfo.bmWidth;
	m_nBmpHeight = bmpInfo.bmHeight;
	
	m_fRateX = m_fRateY = 1;

	m_nColCount = m_nRowCount = 10;

	m_nCellHeight = m_nCellWidth = 50;
	m_nOrginX = m_nOrginY = 50;

	bmp.DeleteObject();
	m_LocalChessPT.x = m_LocalChessPT.y = -1;
	m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;

}


void CChessBorad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChessBorad)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChessBorad, CDialog)
	//{{AFX_MSG_MAP(CChessBorad)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessBorad message handlers

void CChessBorad::OnOK() 
{

}

void CChessBorad::OnCancel() 
{

}

void CChessBorad::OnPaint() 
{
	CPaintDC dc(this); 
	
	//加载棋盘位图
	CBitmap bmp;
	bmp.LoadBitmap(IDB_CHESSBOARD);
	int nBmpWidth,nBmpHeight;
	//获取位图信息
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	nBmpWidth = bmpInfo.bmWidth;
	nBmpHeight = bmpInfo.bmHeight;

	//将位图绘制在整个窗口区域
	CRect cltRC;
	GetClientRect(cltRC);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(&bmp);

	dc.StretchBlt(0,0,cltRC.Width(),cltRC.Height(),&memDC,0,0,nBmpWidth,nBmpHeight,SRCCOPY);
	memDC.DeleteDC();
	bmp.DeleteObject();

	DrawChessboard();

	CDC* pDC = GetDC();
	CBitmap BmpWhite,BmpBlack,BmpBK;
	memDC.CreateCompatibleDC(pDC);
	BmpBlack.LoadBitmap(IDB_BLACK);
	BmpWhite.LoadBitmap(IDB_WHITE);
	BmpBK.LoadBitmap(IDB_BLANK);

	BmpBlack.GetBitmap(&bmpInfo);
	nBmpWidth = bmpInfo.bmWidth;
	nBmpHeight = bmpInfo.bmHeight;
	
	if (m_IsWin)
	{
		CPen pen(PS_SOLID,2,RGB(255,0,0));
		pDC->SelectObject(&pen);

		
		pDC->MoveTo(m_NodeList[m_Startpt.x][m_Startpt.y].m_Point);
		pDC->LineTo(m_NodeList[m_Endpt.x][m_Endpt.y].m_Point);
	}

	int nPosX,nPosY;
	nPosX = 10*m_fRateX;
	nPosY = 10*m_fRateY;
//	nBmpWidth = 22*m_fRateX;
//	nBmpHeight = 22*m_fRateY;

#pragma region //当前处于回放状态进行的操作
	if (m_bBackPlay)	//当前是否为游戏回放
	{
		POSITION pos = NULL;
		for(pos = m_BackPlayList.GetHeadPosition(); pos != NULL;)
		{
			NODE* pNode = (NODE*)m_BackPlayList.GetNext(pos);
			if (pNode->m_IsUsed==TRUE)
			{
				int nPosX,nPosY;
				nPosX = 10*m_fRateX;
				nPosY = 10*m_fRateY;

				if (pNode->m_Color == ncWHITE)
				{
					memDC.SelectObject(&BmpWhite);
					pDC->StretchBlt(pNode->m_Point.x-nPosX,pNode->m_Point.y-nPosY,nBmpWidth,nBmpHeight,
						&memDC,0,0,nBmpWidth,nBmpHeight,SRCCOPY);
				}
				else if (pNode->m_Color == ncBLACK)
				{
					memDC.SelectObject(&BmpBlack);
					pDC->StretchBlt(pNode->m_Point.x-nPosX,pNode->m_Point.y-nPosY,nBmpWidth,nBmpHeight,
						&memDC,0,0,nBmpWidth,nBmpHeight,SRCCOPY);
				}
				else if (pNode->m_Color == ncUNKOWN)
				{
					memDC.SelectObject(&BmpBK);
					pDC->StretchBlt(pNode->m_Point.x-nPosX,pNode->m_Point.y-nPosY,nBmpWidth,nBmpHeight,
						&memDC,0,0,nBmpWidth,nBmpHeight,SRCCOPY);
					
					//绘制棋盘的局部表格

					//首先获取中心点坐标
					int nCenterX = pNode->m_Point.x ;
					int nCenterY = pNode->m_Point.y;

					CPoint topPT(nCenterX,nCenterY-nPosY);
					CPoint bottomPT(nCenterX,nCenterY+nPosY + 5);
					CPen pen(PS_SOLID,1,RGB(0,0,0));
					pDC->SelectObject(&pen);

					pDC->MoveTo(topPT);
					pDC->LineTo(bottomPT);

					CPoint leftPT(nCenterX-nPosX,nCenterY);
					CPoint rightPT(nCenterX+nPosX + 10 ,nCenterY);
					pDC->MoveTo(leftPT);
					pDC->LineTo(rightPT);

				}
			}
		}
	}
#pragma endregion //结束回访操作
#pragma region //绘制棋子
	else
	{
		for (int m=0; m< m_nRowCount+1; m++)
		{
			for (int n=0; n<m_nColCount+1; n++)
			{
				if (m_NodeList[m][n].m_Color == ncWHITE)
				{
					memDC.SelectObject(&BmpWhite);
					pDC->StretchBlt(m_NodeList[m][n].m_Point.x-nPosX,m_NodeList[m][n].m_Point.y-nPosY,nBmpWidth,nBmpHeight,
						&memDC,0,0,nBmpWidth,nBmpHeight,SRCCOPY);
				}
				else if (m_NodeList[m][n].m_Color == ncBLACK)
				{
					memDC.SelectObject(&BmpBlack);
					pDC->StretchBlt(m_NodeList[m][n].m_Point.x-nPosX,m_NodeList[m][n].m_Point.y-nPosY,nBmpWidth,nBmpHeight,
						&memDC,0,0,nBmpWidth,nBmpHeight,SRCCOPY);

				}
			}
		}
	}

#pragma endregion //结束绘制棋子
	BmpWhite.DeleteObject();
	BmpBlack.DeleteObject();
	BmpBK.DeleteObject();
}

void CChessBorad::DrawChessboard()
{
	CDC* pDC = GetDC();
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	pDC->SelectObject(&pen);
	int nOriginX = m_nOrginX*m_fRateX;
	int nOriginY = m_nOrginY*m_fRateY;
	int nCellWidth = m_nCellWidth*m_fRateX;
	int nCellHeight = m_nCellHeight*m_fRateY;

	for (int i = 0; i<m_nRowCount+1; i++)
	{
		pDC->MoveTo(nOriginX+nCellWidth*(i),nOriginY);
		pDC->LineTo(nOriginX+nCellWidth*(i),nOriginY+m_nRowCount*nCellHeight);
	}
	for (int j = 0; j<m_nColCount+1; j++)
	{
		pDC->MoveTo(nOriginX ,nOriginY+(j)*nCellHeight);
		pDC->LineTo(nOriginX +m_nColCount*nCellWidth,nOriginY+(j)*nCellHeight);
	}
}

void CChessBorad::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	//当窗口大小改变时确定图像的缩放比例
	CRect cltRC;
	GetClientRect(cltRC);
	m_fRateX =  cltRC.Width() / (double)m_nBmpWidth;
	m_fRateY =  cltRC.Height() / (double)m_nBmpHeight;

	int nOriginX = m_nOrginX*m_fRateX;
	int nOriginY = m_nOrginY*m_fRateY;
	int nCellWidth = m_nCellWidth*m_fRateX;
	int nCellHeight = m_nCellHeight*m_fRateY;

	//设置节点的坐标
	for (int i=0; i<m_nRowCount+1; i++)
	{
		for (int j=0; j<m_nColCount+1; j++)
		{
			m_NodeList[i][j].m_Point= CPoint(nOriginX+nCellWidth*j,nOriginY+nCellHeight*i); 	
		}
	}
	POSITION pos;
	for(pos = m_BackPlayList.GetHeadPosition(); pos != NULL;)
	{
		NODE* pNode = (NODE*)m_BackPlayList.GetNext(pos);
		pNode->m_Point= CPoint(nOriginX+nCellWidth*pNode->m_nY,nOriginY+nCellHeight*pNode->m_nX);
	}	
}

BOOL CChessBorad::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int nOriginX = m_nOrginX*m_fRateX;
	int nOriginY = m_nOrginY*m_fRateY;
	int nCellWidth = m_nCellWidth*m_fRateX;
	int nCellHeight = m_nCellHeight*m_fRateY;

	//创建套接字
	m_ClientSock.AttachDlg(this);
	m_ClientSock.Create();

	InitializeNode();

	//设置节点的坐标
	for (int i=0; i<m_nRowCount+1; i++)
	{
		for (int j=0; j<m_nColCount+1; j++)
		{
			m_NodeList[i][j].m_Point= CPoint(nOriginX+nCellWidth*j,nOriginY+nCellHeight*i); 	
		}
	}
	for (int m=0; m<m_nRowCount+1; m++)
	{	for (int n=0; n<m_nColCount+1; n++)
		{
			SetRecentNode(&m_NodeList[m][n]); 	
		}	
	}	
	
	return TRUE;  
}

void CChessBorad::SetRecentNode(NODE *pNode)
{
	int nCellWidth = m_nCellWidth*m_fRateX;
	int nCellHeight = m_nCellHeight*m_fRateY;
	
	int nCurX = pNode->m_nX;
	int nCurY = pNode->m_nY;

	//左上方的临近节点
	if (nCurX > 0 && nCurY >0)
		pNode->m_pRecents[0] = &m_NodeList[nCurX-1][nCurY-1];
	else
		pNode->m_pRecents[0] = NULL;
	//上方临近节点
	if (nCurY > 0)
		pNode->m_pRecents[1] = &m_NodeList[nCurX][nCurY-1];
	else
		pNode->m_pRecents[1] = NULL;
	//右上方临近节点
	if (nCurX < m_nColCount-1 && nCurY > 0)
		pNode->m_pRecents[2] = &m_NodeList[nCurX+1][nCurY-1];
	else
		pNode->m_pRecents[2] = NULL;
	//左方节点临近节点
	if (nCurX >0 )
		pNode->m_pRecents[3] = &m_NodeList[nCurX-1][nCurY];	
	else
		pNode->m_pRecents[3] = NULL;
	//右方节点临近节点
	if (nCurX < m_nColCount-1)
		pNode->m_pRecents[4] = &m_NodeList[nCurX+1][nCurY];	
	else
		pNode->m_pRecents[4] = NULL;
	//左下方临近节点
	if (nCurX >0 && nCurY < m_nRowCount-1)
		pNode->m_pRecents[5] = &m_NodeList[nCurX-1][nCurY+1];	
	else
		pNode->m_pRecents[5] = NULL;
	//下方临近节点
	if (nCurY < m_nRowCount-1)
		pNode->m_pRecents[6] = &m_NodeList[nCurX][nCurY+1];
	else
		pNode->m_pRecents[6] = NULL;
	//右下方临近节点
	if (nCurX < m_nColCount-1 && nCurY < m_nRowCount-1)
		pNode->m_pRecents[7] = &m_NodeList[nCurX+1][nCurY+1];
	else
		pNode->m_pRecents[7] = NULL;
}

NODE* CChessBorad::GetNodeFromPoint(CPoint pt)
{
	for (int i=0; i<m_nRowCount+1; i++)
	{
		for (int j=0; j<m_nColCount+1; j++)
		{
			if (m_NodeList[i][j].m_Point == pt)
				return &m_NodeList[i][j];
		}
	}
	return NULL;
}

void CChessBorad::InitializeNode()
{
	for (int i=0; i<m_nRowCount+1; i++)
	{
		for (int j=0; j<m_nColCount+1; j++)
		{
			m_NodeList[i][j].m_Color = ncUNKOWN;
			m_NodeList[i][j].m_nX = i;
			m_NodeList[i][j].m_nY = j;
		}
	}
	OnPaint();
}

NODE* CChessBorad::IsWin(NODE *pCurrent)
{
	if (pCurrent->m_Color != ncWHITE)
		return NULL;

	//按4个方向判断
	int num = 0; //计数
	//m_Startpt = pCurrent->m_Point;
	//m_Endpt = pCurrent->m_Point;

	m_Startpt.x = pCurrent->m_nX;
	m_Startpt.y = pCurrent->m_nY;
	m_Endpt.x = pCurrent->m_nX;
	m_Endpt.y = pCurrent->m_nY;


	//按垂直方向判断在当前节点按上下两个方向遍历	
	NODE* tmp = pCurrent->m_pRecents[1]; //获得当前节点的上方节点
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)	//遍历上方节点
	{
		m_Startpt.x = tmp->m_nX;// m_Point;
		m_Startpt.y = tmp->m_nY;
		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[1];
	}
	tmp = pCurrent->m_pRecents[6];		//获得当前节点的下方节点
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)	//遍历上方节点
	{
		//m_Endpt = tmp->m_Point;
		m_Endpt.x = tmp->m_nX;
		m_Endpt.y = tmp->m_nY;

		num += 1;
		if ( num >= 4 )
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[6];
	}
	//按水平方向判断在当前节点,按左右两个方向遍历
	num = 0;
	tmp = pCurrent->m_pRecents[3];		//遍历左节点
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
	//	m_Startpt = tmp->m_Point;
		m_Startpt.x = tmp->m_nX;
		m_Startpt.y = tmp->m_nY;
		num += 1;
		if (num >= 4)
		{	
			return tmp;
		}
		tmp = tmp->m_pRecents[3];
	}
	tmp = pCurrent->m_pRecents[4];		//遍历右节点
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
		//m_Endpt = tmp->m_Point;
		m_Endpt.x = tmp->m_nX;
		m_Endpt.y = tmp->m_nY;
		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[4];
	}
	//按135度斜角遍历
	num = 0;
	tmp = pCurrent->m_pRecents[0];		//遍历斜上方节点
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
		//m_Startpt = tmp->m_Point;
		m_Startpt.x = tmp->m_nX;
		m_Startpt.y = tmp->m_nY;

		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[0];
	}
	tmp = pCurrent->m_pRecents[7];		//遍历斜下方节点
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
	//	m_Endpt = tmp->m_Point;
		m_Endpt.x = tmp->m_nX;
		m_Endpt.y = tmp->m_nY;
		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[7];
	}	
	//按45度斜角遍历
	num = 0;
	tmp = pCurrent->m_pRecents[2];		//遍历斜上方节点
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
	//	m_Startpt = tmp->m_Point;
		m_Startpt.x = tmp->m_nX;
		m_Startpt.y = tmp->m_nY;

		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[2];
	}
	tmp = pCurrent->m_pRecents[5];		//遍历斜下方节点
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
		//m_Endpt = tmp->m_Point;
		m_Endpt.x = tmp->m_nX;
		m_Endpt.y = tmp->m_nY;

		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[5];
	}	
	return NULL;
}

void CChessBorad::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CPoint pt = point;
	if (m_IsStart == FALSE)			//游戏终止
		return;

	if (m_IsDown==TRUE)				//轮到客户端
	{
		NODE* node = GetLikeNode(pt); 
		if (node !=NULL)
		{
			if (node->m_Color==ncUNKOWN)
			{

				node->m_Color = ncWHITE;
				NODE *pNode = new NODE();
				memcpy(pNode,node,sizeof(NODE));

				m_BackPlayList.AddTail(pNode);

				OnPaint();
				//定义一个TCP数据报
				TCP_PACKAGE	 package;
				package.cmdType = CT_POINT;
				package.chessPT.x = node->m_nX;
				package.chessPT.y = node->m_nY;

				m_LocalChessPT.x = node->m_nX;
				m_LocalChessPT.y = node->m_nY;

				m_ClientSock.Send((void*)&package,sizeof(TCP_PACKAGE));

				m_IsDown = FALSE;
				if (IsWin(node)!= NULL)
				{
					m_IsStart = FALSE;
					Sleep(1000);


					TCP_PACKAGE	 winPackage;
					winPackage.cmdType = CT_WINPOINT;
					winPackage.winPT[0] = m_Startpt;
					winPackage.winPT[1] = m_Endpt;

					m_ClientSock.Send((void*)&winPackage,sizeof(TCP_PACKAGE));

					m_IsWin = TRUE;
					m_State = esEND;

					Invalidate();
					MessageBox("恭喜你,赢了!!!");
					m_IsWin = FALSE;
					InitializeNode();
					Invalidate();
					m_LocalChessPT.x = m_LocalChessPT.y = -1;
					m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;
				}
			}
		}
	}	
	CDialog::OnLButtonUp(nFlags, point);
}

NODE* CChessBorad::GetLikeNode(CPoint pt)
{
	CPoint tmp;	
	for (int i = 0 ;i<m_nRowCount+1;i++)
		for (int j = 0; j<m_nColCount+1;j++)
		{
			tmp = m_NodeList[i][j].m_Point;

			int nSizeX = 10 * m_fRateX;
			int nSizeY = 10 * m_fRateY;

			CRect rect(tmp.x-nSizeX,tmp.y-nSizeY,tmp.x+nSizeX,tmp.y+nSizeY);		
			if (rect.PtInRect(pt))
				return &m_NodeList[i][j];
		}
	return NULL;
}

void CChessBorad::BeginGame()
{
	if (!m_IsConnect)
	{
		CSrvInfo srvDlg;
		if (srvDlg.DoModal() == IDOK)
		{
			if (!srvDlg.m_IP.IsEmpty())
			{
				m_ClientSock.Close();
				int err = m_ClientSock.Create();
				BOOL ret = m_ClientSock.Connect(srvDlg.m_IP,srvDlg.m_Port);
				if (ret == FALSE)
				{
					m_IsConnect = FALSE;
					MessageBox("连接服务器失败!");				
					return;
				}
				else
				{
					m_IsConnect = TRUE;


					//设置用户信息
					CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
					pDlg->m_RightPanel.m_NetState.SetWindowText("网路状态:已连接");

					int nItem  = 0;
					if ( pDlg->m_RightPanel.m_UserList.GetItemCount() <1)
					{
						nItem = pDlg->m_RightPanel.m_UserList.InsertItem(0,"");
					}
					CTime tmNow = CTime::GetCurrentTime();
					CString csFormat = tmNow.Format("%H:%M:%S");
					
					if (srvDlg.m_NickName.IsEmpty())
					{
						srvDlg.m_NickName = "匿名";
					}
					pDlg->m_RightPanel.m_UserList.SetItemText(nItem,0,srvDlg.m_NickName);
					CString csIP;
					UINT nPort;
					m_ClientSock.GetSockName(csIP,nPort);
					pDlg->m_RightPanel.m_UserList.SetItemText(nItem,1,csIP);
					pDlg->m_RightPanel.m_UserList.SetItemText(nItem,2,csFormat);


					CString csUser = "\r\n昵称:";
					csUser += srvDlg.m_NickName;
					csUser += "\r\n";
					csUser += "IP:";
					csUser += srvDlg.m_IP;
					pDlg->m_RightPanel.m_User.SetWindowText(csUser);

					//设置服务器信息
					nItem = 1;
					if (pDlg->m_RightPanel.m_UserList.GetItemCount() < 2)
					{
						nItem = pDlg->m_RightPanel.m_UserList.InsertItem(1,"");
					}
					
					pDlg->m_RightPanel.m_UserList.SetItemText(nItem,1,srvDlg.m_IP);
					pDlg->m_RightPanel.m_UserList.SetItemText(nItem,2,csFormat);

					m_csNickName = srvDlg.m_NickName;
					if (m_csNickName.IsEmpty())
					{
						m_csNickName = "匿名";
					}

					//发送游戏开始的信息
					TCP_PACKAGE tcpPackage;
					memset(&tcpPackage,0,sizeof(TCP_PACKAGE));
					tcpPackage.cmdType = CT_BEGINGAME;
					strncpy(tcpPackage.chText,m_csNickName,512);

					m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));

					m_LocalChessPT.x = m_LocalChessPT.y = -1;
					m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;

								
					//清空回放列表
					FreeBackPlayList();
					InitBackPlayNode();
					m_bBackPlay = FALSE;
					Invalidate();

					KillTimer(1);
					SetTimer(1,1000,NULL);
				}
			}
		}
	}
	else if (m_State == esBEGIN)
	{
		MessageBox("游戏进行中!");
	}
	else if (m_State == esEND)		//游戏结束，开始新的游戏,发出游戏开始的请求
	{

		m_IsDown = TRUE;
		m_IsStart = FALSE;
		m_IsWin = FALSE;


		TCP_PACKAGE tcpPackage;
		memset(&tcpPackage,0,sizeof(TCP_PACKAGE));
		tcpPackage.cmdType = CT_BEGINGAME;
		if (m_csNickName.IsEmpty())
		{
			m_csNickName = "匿名";
		}
		strncpy(tcpPackage.chText,m_csNickName,512);
		m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));

		m_LocalChessPT.x = m_LocalChessPT.y = -1;
		m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;


	}
}

void CChessBorad::ReceiveData()
{
	BYTE* pBuffer = new BYTE[sizeof(TCP_PACKAGE)];

	int factlen = m_ClientSock.Receive(pBuffer,sizeof(TCP_PACKAGE));
	if (factlen == sizeof(TCP_PACKAGE))
	{
		TCP_PACKAGE tcpPackage;
		memcpy(&tcpPackage,pBuffer,sizeof(TCP_PACKAGE));
		if (tcpPackage.cmdType == CT_NETTEST )//测试网络状态
		{
			m_TestNum = 0;   //相当于一个计时器，当此计时器的值大于3时，表明网络已经断开
			m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));		
		}
		else if (tcpPackage.cmdType == CT_BEGINGAME)//开始游戏
		{

			InitializeNode();
			m_IsStart = TRUE;

			m_State = esBEGIN;	
			
			//设置对方昵称
			CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
			pDlg->m_RightPanel.m_UserList.SetItemText(1,0,tcpPackage.chText);
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;
			
			FreeBackPlayList();
			m_bBackPlay = FALSE;
			MessageBox("游戏开始");			
		
		}
		else if (tcpPackage.cmdType == CT_POINT)//客户端棋子坐标信息
		{
			int nX = tcpPackage.chessPT.x;
			int nY = tcpPackage.chessPT.y;
			m_RemoteChessPT.x = nX ;
			m_RemoteChessPT.y = nY ;
			m_NodeList[nX][nY].m_Color = ncBLACK;

			NODE *pNode = new NODE();
			memcpy(pNode,&m_NodeList[nX][nY],sizeof(NODE));
			m_BackPlayList.AddTail(pNode);

			OnPaint();	
			m_IsDown = TRUE;
		}
		else if (tcpPackage.cmdType == CT_WINPOINT)//客户端赢了，客户端棋子起始和终止坐标信息
		{

			int nStartX = tcpPackage.winPT[0].x;
			int nStartY = tcpPackage.winPT[0].y;
			int nEndX = tcpPackage.winPT[1].x;
			int nEndY = tcpPackage.winPT[1].y;
			
			m_Startpt = tcpPackage.winPT[0];
			m_Endpt = tcpPackage.winPT[1];

			m_IsDown = FALSE;
			m_IsStart = FALSE;

			m_IsWin = TRUE;
			m_State = esEND;
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;
			Invalidate();
			MessageBox("你输了!!!");
			m_IsWin = FALSE;
			InitializeNode();
			Invalidate();
			
		}
		else if (tcpPackage.cmdType == CT_TEXT)	//文本信息
		{
			CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
			//获取对方昵称
			CString csNickName =  pDlg->m_RightPanel.m_UserList.GetItemText(1,0);
			CString csText = csNickName;
			csText += "说:";
			csText += tcpPackage.chText;

			pDlg->m_RightPanel.m_MsgList.SetSel(-1,-1);
			pDlg->m_RightPanel.m_MsgList.ReplaceSel(csText);
			pDlg->m_RightPanel.m_MsgList.SetSel(-1,-1);
			pDlg->m_RightPanel.m_MsgList.ReplaceSel("\n");
		
		}
		else if (tcpPackage.cmdType == CT_BACKDENY)	//对方拒绝悔棋
		{
			MessageBox("对方拒绝悔棋!","提示");
		}
		else if (tcpPackage.cmdType == CT_BACKACCEPTANCE)//对方同意悔棋
		{
			CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
			//判断是否该本地用户下棋了,如果是则需要撤销之前对方下的棋子，然后再撤销本地用户下的棋子
			if (m_IsDown==TRUE)	
			{
				int nPosX = m_RemoteChessPT.x;
				int nPosY = m_RemoteChessPT.y;
				if (nPosX > -1 && nPosY > -1)
				{
					m_NodeList[nPosX][nPosY].m_Color = ncUNKOWN;	
					NODE *pNode = new NODE();
					memcpy(pNode,&m_NodeList[nPosX][nPosY],sizeof(NODE));
					m_BackPlayList.AddTail(pNode);

				}
				nPosX = m_LocalChessPT.x;
				nPosY = m_LocalChessPT.y;
				if (nPosX > -1 && nPosY > -1)
				{
					m_NodeList[nPosX][nPosY].m_Color = ncUNKOWN;
					NODE *pNode = new NODE();
					memcpy(pNode,&m_NodeList[nPosX][nPosY],sizeof(NODE));
					m_BackPlayList.AddTail(pNode);					
				}
				//刷新窗口
				Invalidate();
			
			}
			else	//该对方下棋了,只撤销本地用户下的棋子
			{
				int nPosX = m_LocalChessPT.x;
				int nPosY =m_LocalChessPT.y;
				if (nPosX > -1 && nPosY > -1)
				{
					m_NodeList[nPosX][nPosY].m_Color = ncUNKOWN;

					NODE *pNode = new NODE();
					memcpy(pNode,&m_NodeList[nPosX][nPosY],sizeof(NODE));
					m_BackPlayList.AddTail(pNode);
					//刷新窗口
					Invalidate();
					m_IsDown = TRUE;	
				}
			}
			m_LocalChessPT.x  = -1;
			m_LocalChessPT.y  = -1;
			m_RemoteChessPT.x = -1;
			m_RemoteChessPT.y = -1;
		}
		else if (tcpPackage.cmdType == CT_BACKREQUEST)	//对方发送悔棋请求
		{
			if (MessageBox("是否同意悔棋?","提示",MB_YESNO)==IDYES)
			{
				CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
				//接收悔棋
				tcpPackage.cmdType = CT_BACKACCEPTANCE;
				m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));	
				//进行本地的悔棋处理
				
				if (m_IsDown==TRUE)	//该本地下棋了，只需要撤销一步
				{
					int nPosX = m_RemoteChessPT.x;
					int nPosY = m_RemoteChessPT.y;
					if (nPosX > -1 && nPosY > -1)
					{
						m_NodeList[nPosX][nPosY].m_Color = ncUNKOWN;
						NODE *pNode = new NODE();
						memcpy(pNode,&m_NodeList[nPosX][nPosY],sizeof(NODE));
						m_BackPlayList.AddTail(pNode);

						//刷新窗口
						Invalidate();
					}
					m_IsDown = FALSE;
				}
				else	//该对方下棋了，需要撤销两步
				{
	
					int nPosX = m_LocalChessPT.x;
					int nPosY = m_LocalChessPT.y;
					
					if (nPosX > -1 && nPosY > -1)
					{
						m_NodeList[nPosX][nPosY].m_Color = ncUNKOWN;

						NODE *pNode = new NODE();
						memcpy(pNode,&m_NodeList[nPosX][nPosY],sizeof(NODE));
						m_BackPlayList.AddTail(pNode);

					}

					nPosX = m_RemoteChessPT.x;
					nPosY = m_RemoteChessPT.y;
					if (nPosX > -1 && nPosY > -1)
					{
						m_NodeList[nPosX][nPosY].m_Color = ncUNKOWN;

						NODE *pNode = new NODE();
						memcpy(pNode,&m_NodeList[nPosX][nPosY],sizeof(NODE));
						m_BackPlayList.AddTail(pNode);

					}
					//刷新窗口
					Invalidate();
				}

				m_LocalChessPT.x  = -1;
				m_LocalChessPT.y  = -1;
				m_RemoteChessPT.x = -1;
				m_RemoteChessPT.y = -1;

			}
			else		//拒绝悔棋
			{
				tcpPackage.cmdType = CT_BACKDENY;
				m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));	
			}
		}
		else if (tcpPackage.cmdType == CT_DRAWCHESSACCEPTANCE)	//对方接收和棋请求
		{
			CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
			//进行和棋处理，游戏结束
			m_TestNum = 0;

			m_IsDown = FALSE;
			m_IsStart = FALSE;
			m_IsWin = FALSE;
			m_State = esEND;
			InitializeNode();
			//更新界面
			Invalidate();
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;	
			MessageBox("对方同意和棋!","提示");
		
		}
		else if (tcpPackage.cmdType == CT_DRAWCHESSDENY)	//对方拒绝和棋
		{
			MessageBox("对方拒绝了和棋!","提示");
		}
		else if (tcpPackage.cmdType == CT_DRAWCHESSREQUEST)	//对方发出和棋请求
		{
			CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
			if (MessageBox("对方要求和棋，是否同意和棋?","提示",MB_YESNO)==IDYES)
			{		//同意和棋
				tcpPackage.cmdType = CT_DRAWCHESSACCEPTANCE;
				m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));
				
				//进行和棋处理，游戏结束
				m_TestNum = 0;

				m_IsDown = FALSE;
				m_IsStart = FALSE;
				m_IsWin = FALSE;
				m_State = esEND;
				InitializeNode();
				//更新界面
				Invalidate();
				m_LocalChessPT.x = m_LocalChessPT.y = -1;
				m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;

			}
			else	//拒绝和棋
			{
				tcpPackage.cmdType = CT_DRAWCHESSDENY;
				m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));		
			}
		}
		else if (tcpPackage.cmdType == CT_GIVEUP)			//对方认输了
		{
			CClientFiveChessDlg *pDlg = (CClientFiveChessDlg*)GetParent();
			//结束游戏
			m_TestNum = 0;

			m_IsDown = FALSE;
			m_IsStart = FALSE;
			m_IsWin = FALSE;
			m_State = esEND;
			InitializeNode();
			//更新界面
			Invalidate();
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;


			MessageBox("您获胜了!","提示");
		}

	}
  
	delete []pBuffer;
	
}

void CChessBorad::OnTimer(UINT nIDEvent) 
{
	if (m_IsConnect)
	{
		m_TestNum++;
		if (m_TestNum > 3)	//与对方断开连接
		{
			m_TestNum = 0;
			m_IsConnect = FALSE;
			m_IsDown = FALSE;
			m_IsStart = FALSE;
			m_IsWin = FALSE;
			m_State = esEND;
			m_IsConnect = FALSE;
			InitializeNode();
			CClientFiveChessDlg * pDlg = (CClientFiveChessDlg*)GetParent();
			pDlg->m_RightPanel.m_NetState.SetWindowText("网路状态:断开连接");
			//更新界面
			Invalidate();
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CChessBorad::InitBackPlayNode()
{
	POSITION pos;
	for(pos = m_BackPlayList.GetHeadPosition(); pos != NULL;)
	{
		NODE* pNode = (NODE*)m_BackPlayList.GetNext(pos);
		pNode->m_IsUsed = FALSE;
	}
}

void CChessBorad::FreeBackPlayList()
{
	if (m_BackPlayList.GetCount()>0)
	{
		POSITION pos; 
		for (pos = m_BackPlayList.GetHeadPosition();pos != NULL;)

		{
			NODE *pNode = (NODE*)m_BackPlayList.GetNext(pos);
			delete pNode;
		}
		m_BackPlayList.RemoveAll();
	}
}

void CChessBorad::GamePlayBack()
{

	CDC* pDC = GetDC();
	CDC memDC;
	CBitmap BmpWhite,BmpBlack,BmpBK;
	memDC.CreateCompatibleDC(pDC);
	BmpBlack.LoadBitmap(IDB_BLACK);
	BmpWhite.LoadBitmap(IDB_WHITE);
	BmpBK.LoadBitmap(IDB_BLANK);

	//获取位图信息
	BITMAP bmpInfo;
	BmpBlack.GetBitmap(&bmpInfo);
	int nBmpWidth = bmpInfo.bmWidth;
	int nBmpHeight = bmpInfo.bmHeight;
	POSITION pos = NULL;

	m_bBackPlay = FALSE;
	InitBackPlayNode();  //将backList中的节点的m_isused属性设置为false（m_IsUsed属性标识棋子是否被使用）
	OnPaint();
	m_bBackPlay = TRUE;

	for(pos = m_BackPlayList.GetHeadPosition(); pos != NULL;)
	{
		NODE* pNode = (NODE*)m_BackPlayList.GetNext(pos);
	

		int nPosX,nPosY;
		nPosX = 10*m_fRateX;
		nPosY = 10*m_fRateY;
		pNode->m_IsUsed = TRUE;
	
		if (pNode->m_Color == ncWHITE)
		{
			memDC.SelectObject(&BmpWhite);
			pDC->StretchBlt(pNode->m_Point.x-nPosX,pNode->m_Point.y-nPosY,nBmpWidth,nBmpHeight,
				&memDC,0,0,nBmpWidth,nBmpHeight,SRCCOPY);
		}
		else if (pNode->m_Color == ncBLACK)
		{
			memDC.SelectObject(&BmpBlack);
			pDC->StretchBlt(pNode->m_Point.x-nPosX,pNode->m_Point.y-nPosY,nBmpWidth,nBmpHeight,
				&memDC,0,0,nBmpWidth,nBmpHeight,SRCCOPY);
		}
		else if (pNode->m_Color == ncUNKOWN)
		{
			memDC.SelectObject(&BmpBK);
			pDC->StretchBlt(pNode->m_Point.x-nPosX,pNode->m_Point.y-nPosY,nBmpWidth,nBmpHeight,
				&memDC,0,0,nBmpWidth,nBmpHeight,SRCCOPY);
			
			//绘制棋盘的局部表格

			//首先获取中心点坐标
			int nCenterX = pNode->m_Point.x ;
			int nCenterY = pNode->m_Point.y;

			CPoint topPT(nCenterX,nCenterY-nPosY);
			CPoint bottomPT(nCenterX,nCenterY+nPosY + 5);
			CPen pen(PS_SOLID,1,RGB(0,0,0));
			pDC->SelectObject(&pen);

			pDC->MoveTo(topPT);
			pDC->LineTo(bottomPT);

			CPoint leftPT(nCenterX-nPosX,nCenterY);
			CPoint rightPT(nCenterX+nPosX + 10 ,nCenterY);
			pDC->MoveTo(leftPT);
			pDC->LineTo(rightPT);
		}

		//延时
		SYSTEMTIME beginTime,endTime;
		GetSystemTime(&beginTime);	
		if (beginTime.wSecond > 58)
			beginTime.wSecond = 58;
		
		while (true)
		{

			MSG msg;
			::GetMessage(&msg,0,0,WM_USER);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			GetSystemTime(&endTime);
			if (endTime.wSecond ==0 )
				endTime.wSecond = 59;
			if (endTime.wSecond > beginTime.wSecond)
				break;
		}
	}

	BmpWhite.DeleteObject();
	BmpBlack.DeleteObject();
	BmpBK.DeleteObject();
	memDC.DeleteDC();

	MessageBox("游戏回放结束!","提示");

}
