// ChessBorad.cpp : implementation file
//

#include "stdafx.h"
#include "SrvFiveChess.h"
#include "ChessBorad.h"
#include "ServerSetting.h"
#include "SrvFiveChessDlg.h"

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
	m_ConfigSrv = FALSE;
	m_bBackPlay = FALSE;


	//��������λͼ
	CBitmap bmp;
	bmp.LoadBitmap(IDB_CHESSBOARD);
	
	//��ȡλͼ��Ϣ
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	m_nBmpWidth = bmpInfo.bmWidth;
	m_nBmpHeight = bmpInfo.bmHeight;
	
	m_fRateX = m_fRateY = 1;

	m_nColCount = m_nRowCount = 10;
	m_nCellHeight = m_nCellWidth = 50;
	m_nOrginX = m_nOrginY = 50;

	m_TestNum = 0;

	m_LocalChessPT.x = m_LocalChessPT.y = -1;
	m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;

	bmp.DeleteObject();
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
	
	//��������λͼ
	CBitmap bmp;
	bmp.LoadBitmap(IDB_CHESSBOARD);
	int nBmpWidth,nBmpHeight;
	//��ȡλͼ��Ϣ
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	nBmpWidth = bmpInfo.bmWidth;
	nBmpHeight = bmpInfo.bmHeight;

	//��λͼ������������������
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

	if (m_bBackPlay)	//��ǰ�Ƿ�Ϊ��Ϸ�ط�
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
					
					//�������̵ľֲ����
					//���Ȼ�ȡ���ĵ�����
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
	else	//�������л�������
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
	BmpWhite.DeleteObject();
	BmpBlack.DeleteObject();
	BmpBK.DeleteObject();


}

void CChessBorad::DrawChessboard()
{
	CDC* pDC = GetDC();
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	pDC->SelectObject(&pen);
	//��������������
	int nOriginX = m_nOrginX*m_fRateX;
	int nOriginY = m_nOrginY*m_fRateY;
	//���㵥Ԫ��Ŀ�Ⱥ͸߶�
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
	//�����ڴ�С�ı�ʱȷ��ͼ������ű���
	CRect cltRC;
	GetClientRect(cltRC);
	m_fRateX =  cltRC.Width() / (double)m_nBmpWidth;
	m_fRateY =  cltRC.Height() / (double)m_nBmpHeight;
	int nOriginX = m_nOrginX*m_fRateX;
	int nOriginY = m_nOrginY*m_fRateY;
	int nCellWidth = m_nCellWidth*m_fRateX;
	int nCellHeight = m_nCellHeight*m_fRateY;
	//���ýڵ������
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
	//�����׽���
	m_ClientSock.AttachDlg(this);
	m_SrvSock.AttachDlg(this);
	m_ClientSock.Create();
	InitializeNode();
	//������������
	for (int i=0; i<m_nRowCount+1; i++)
	{
		for (int j=0; j<m_nColCount+1; j++)
		{
			m_NodeList[i][j].m_Point= CPoint(nOriginX+nCellWidth*j,nOriginY+nCellHeight*i); 	
		}
	}
	for (int m=0; m<m_nRowCount+1; m++)
	{
		for (int n=0; n<m_nColCount+1; n++)
		{
			SetRecentNode(&m_NodeList[m][n]); 	
		}	
	}		
	return TRUE;  
}

void CChessBorad::SetRecentNode(NODE *pNode)
{
	int nCurX = pNode->m_nX;
	int nCurY = pNode->m_nY;

	//���Ϸ����ٽ��ڵ�
	if (nCurX > 0 && nCurY >0)
		pNode->m_pRecents[0] = &m_NodeList[nCurX-1][nCurY-1];
	else
		pNode->m_pRecents[0] = NULL;
	//�Ϸ��ٽ��ڵ�
	if (nCurY > 0)
		pNode->m_pRecents[1] = &m_NodeList[nCurX][nCurY-1];
	else
		pNode->m_pRecents[1] = NULL;
	//���Ϸ��ٽ��ڵ�
	if (nCurX < m_nColCount-1 && nCurY > 0)
		pNode->m_pRecents[2] = &m_NodeList[nCurX+1][nCurY-1];
	else
		pNode->m_pRecents[2] = NULL;
	//�󷽽ڵ��ٽ��ڵ�
	if (nCurX >0 )
		pNode->m_pRecents[3] = &m_NodeList[nCurX-1][nCurY];	
	else
		pNode->m_pRecents[3] = NULL;
	//�ҷ��ڵ��ٽ��ڵ�
	if (nCurX < m_nColCount-1)
		pNode->m_pRecents[4] = &m_NodeList[nCurX+1][nCurY];	
	else
		pNode->m_pRecents[4] = NULL;
	//���·��ٽ��ڵ�
	if (nCurX >0 && nCurY < m_nRowCount-1)
		pNode->m_pRecents[5] = &m_NodeList[nCurX-1][nCurY+1];	
	else
		pNode->m_pRecents[5] = NULL;
	//�·��ٽ��ڵ�
	if (nCurY < m_nRowCount-1)
		pNode->m_pRecents[6] = &m_NodeList[nCurX][nCurY+1];
	else
		pNode->m_pRecents[6] = NULL;
	//���·��ٽ��ڵ�
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
	if (pCurrent->m_Color != ncBLACK)
		return NULL;
	//��4�������ж�
	int num = 0; //����
	m_Startpt.x = pCurrent->m_nX;
	m_Startpt.y = pCurrent->m_nY;
	m_Endpt.x = pCurrent->m_nX;
	m_Endpt.y = pCurrent->m_nY;

	//����ֱ�����ж��ڵ�ǰ�ڵ㰴���������������	
	NODE* tmp = pCurrent->m_pRecents[1]; //��õ�ǰ�ڵ���Ϸ��ڵ�
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)	//�����Ϸ��ڵ�
	{
		m_Startpt.x = tmp->m_nX;
		m_Startpt.y = tmp->m_nY;
		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[1];
	}
	tmp = pCurrent->m_pRecents[6];		//��õ�ǰ�ڵ���·��ڵ�
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)	//�����Ϸ��ڵ�
	{

		m_Endpt.x = tmp->m_nX;
		m_Endpt.y = tmp->m_nY;

		num += 1;
		if ( num >= 4 )
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[6];
	}
	//��ˮƽ�����ж��ڵ�ǰ�ڵ�,�����������������
	num = 0;
	tmp = pCurrent->m_pRecents[3];		//������ڵ�
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{

		m_Startpt.x = tmp->m_nX;
		m_Startpt.y = tmp->m_nY;
		num += 1;
		if (num >= 4)
		{	
			return tmp;
		}
		tmp = tmp->m_pRecents[3];
	}
	tmp = pCurrent->m_pRecents[4];		//�����ҽڵ�
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{

		m_Endpt.x = tmp->m_nX;
		m_Endpt.y = tmp->m_nY;
		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[4];
	}
	//��135��б�Ǳ���
	num = 0;
	tmp = pCurrent->m_pRecents[0];		//����б�Ϸ��ڵ�
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
		m_Startpt.x = tmp->m_nX;
		m_Startpt.y = tmp->m_nY;

		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[0];
	}
	tmp = pCurrent->m_pRecents[7];		//����б�·��ڵ�
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
		m_Endpt.x = tmp->m_nX;
		m_Endpt.y = tmp->m_nY;
		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[7];
	}	
	//��45��б�Ǳ���
	num = 0;
	tmp = pCurrent->m_pRecents[2];		//����б�Ϸ��ڵ�
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
		m_Startpt.x = tmp->m_nX;
		m_Startpt.y = tmp->m_nY;

		num += 1;
		if (num >= 4)
		{
			return tmp;
		}
		tmp = tmp->m_pRecents[2];
	}
	tmp = pCurrent->m_pRecents[5];		//����б�·��ڵ�
	while (tmp != NULL && tmp->m_Color==pCurrent->m_Color)
	{
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
	if (m_IsStart == FALSE)			//��Ϸ��ֹ
		return;
	if (m_IsDown==TRUE)				//�ֵ��ͻ���
	{
		NODE* node = GetLikeNode(pt); 
		if (node !=NULL)
		{
			if (node->m_Color==ncUNKOWN)
			{
				node->m_Color = ncBLACK;

				NODE *pNode = new NODE();
				memcpy(pNode,node,sizeof(NODE));

				m_BackPlayList.AddTail(pNode);

				OnPaint();

				//����һ��TCP���ݱ�
				TCP_PACKAGE	 package;
				package.cmdType = CT_POINT;
				package.chessPT.x = node->m_nX;
				package.chessPT.y = node->m_nY;
				m_ClientSock.Send((void*)&package,sizeof(TCP_PACKAGE));
				
				//��¼�������������
				m_LocalChessPT.x = node->m_nX;
				m_LocalChessPT.y = node->m_nY;

				m_IsDown= FALSE;
				if (IsWin(node)!= NULL)
				{
					m_IsStart = FALSE;
					Sleep(1000);

					//Ӯ��
					TCP_PACKAGE	 winPackage;
					winPackage.cmdType = CT_WINPOINT;
					winPackage.winPT[0] = m_Startpt;
					winPackage.winPT[1] = m_Endpt;

					m_ClientSock.Send((void*)&winPackage,sizeof(TCP_PACKAGE));

					m_IsWin = TRUE;
					m_State = esEND;
					Invalidate();
					MessageBox("��ϲ��,Ӯ��!!!");
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
	//������������ʼ��Ϸ����
	if (m_IsConnect)	//�ͻ��˵�ǰ������֮��������
	{
		if (m_State!=esBEGIN)	//��Ϸ�ѽ�����δ��ʼ
		{
			m_IsDown = TRUE;
			m_IsStart = FALSE;
			m_IsWin = FALSE;

			CSrvFiveChessDlg *pDlg = (CSrvFiveChessDlg*)GetParent();

			TCP_PACKAGE tcpPackage;
			memset(&tcpPackage,0,sizeof(TCP_PACKAGE));
			tcpPackage.cmdType = CT_BEGINGAME;

			Start();
			//��ȡ�������ǳ�
			CString csNickName;
			csNickName = pDlg->m_RightPanel.m_UserList.GetItemText(0,0);
			if (csNickName.IsEmpty())
				csNickName = "����";
			strncpy(tcpPackage.chText,csNickName,512);
			m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));
			m_TestNum = 0;
			KillTimer(1);
			//��ʼ�������
			SetTimer(1,1000,NULL);

			m_State = esBEGIN;
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;
			
			//��ջط��б�
			FreeBackPlayList();
			InitBackPlayNode();
			m_bBackPlay = FALSE;
			Invalidate();
		
		}
		else
		{
			MessageBox("��Ϸ������!");
		}
	
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

		if (tcpPackage.cmdType == CT_NETTEST )//��������״̬
		{
			m_TestNum = 0;
			CSrvFiveChessDlg * pDlg = (CSrvFiveChessDlg*)GetParent();
			pDlg->m_RightPanel.m_NetState.SetWindowText("��·״̬:������");
			m_IsConnect = TRUE;
			
		}
		else if (tcpPackage.cmdType == CT_BEGINGAME)//��ʼ��Ϸ
		{
			CSrvFiveChessDlg *pDlg = (CSrvFiveChessDlg*)GetParent();
			//�����û��ǳ�
			pDlg->m_RightPanel.m_UserList.SetItemText(1,0,tcpPackage.chText);

			Start();
			//��ȡ�������ǳ�
			CString csNickName;
			csNickName = pDlg->m_RightPanel.m_UserList.GetItemText(0,0);
			if (csNickName.IsEmpty())
				csNickName = "����";
			strncpy(tcpPackage.chText,csNickName,512);
			m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));
			m_TestNum = 0;
			KillTimer(1);
			//��ʼ�������
			SetTimer(1,2000,NULL);

			m_State = esBEGIN;
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;

			FreeBackPlayList();
			m_bBackPlay = FALSE;
		}
		else if (tcpPackage.cmdType == CT_POINT)//�ͻ�������������Ϣ
		{
			int nX = tcpPackage.chessPT.x;
			int nY = tcpPackage.chessPT.y;
			m_NodeList[nX][nY].m_Color = ncWHITE;
			NODE *pNode = new NODE();
			memcpy(pNode,&m_NodeList[nX][nY],sizeof(NODE));
			m_BackPlayList.AddTail(pNode);
			
			m_RemoteChessPT.x = nX;
			m_RemoteChessPT.y = nY;

			OnPaint();	
			m_IsDown = TRUE;
		}
		else if (tcpPackage.cmdType == CT_WINPOINT)//�ͻ���Ӯ�ˣ��ͻ���������ʼ����ֹ������Ϣ
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
			Invalidate();
			MessageBox("������!!!");
			m_IsWin = FALSE;
			InitializeNode();
			Invalidate();	

			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;

		}
		else if (tcpPackage.cmdType == CT_TEXT)	//�ı���Ϣ
		{
			CSrvFiveChessDlg *pDlg = (CSrvFiveChessDlg*)GetParent();
			//��ȡ�Է��ǳ�
			CString csNickName =  pDlg->m_RightPanel.m_UserList.GetItemText(1,0);
			CString csText = csNickName;
			csText += "˵:";
			csText += tcpPackage.chText;
			pDlg->m_RightPanel.m_MsgList.SetSel(-1,-1);
			pDlg->m_RightPanel.m_MsgList.ReplaceSel(csText);
			pDlg->m_RightPanel.m_MsgList.SetSel(-1,-1);
			pDlg->m_RightPanel.m_MsgList.ReplaceSel("\n");

		}
		else if (tcpPackage.cmdType == CT_BACKDENY)	//�Է��ܾ�����
		{
			MessageBox("�Է��ܾ�����!","��ʾ");
		}
		else if (tcpPackage.cmdType == CT_BACKACCEPTANCE)//�Է�ͬ�����
		{
			CSrvFiveChessDlg *pDlg = (CSrvFiveChessDlg*)GetParent();
			//�ж��Ƿ�ñ����û�������,���������Ҫ����֮ǰ�Է��µ����ӣ�Ȼ���ٳ��������û��µ�����
			if (pDlg->m_ChessBoard.m_IsDown==TRUE)	
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
				//ˢ�´���
				Invalidate();
			
			}
			else	//�öԷ�������,ֻ���������û��µ�����
			{
				int nPosX = m_LocalChessPT.x;
				int nPosY = m_LocalChessPT.y;
				if (nPosX > -1 && nPosY > -1)
				{
					m_NodeList[nPosX][nPosY].m_Color = ncUNKOWN;

					NODE *pNode = new NODE();
					memcpy(pNode,&m_NodeList[nPosX][nPosY],sizeof(NODE));
					m_BackPlayList.AddTail(pNode);


					//ˢ�´���
					Invalidate();
					m_IsDown = TRUE;	

				}
			}
			m_LocalChessPT.x  = -1;
			m_LocalChessPT.y  = -1;
			m_RemoteChessPT.x = -1;
			m_RemoteChessPT.y = -1;
		}
		else if (tcpPackage.cmdType == CT_BACKREQUEST)	//�Է����ͻ�������
		{
			if (MessageBox("�Ƿ�ͬ�����?","��ʾ",MB_YESNO)==IDYES)
			{
				CSrvFiveChessDlg *pDlg = (CSrvFiveChessDlg*)GetParent();
				//���ջ���
				tcpPackage.cmdType = CT_BACKACCEPTANCE;
				m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));	
				//���б��صĻ��崦��
				
				if (m_IsDown==TRUE)	//�ñ��������ˣ�ֻ��Ҫ����һ��
				{
					int nPosX = m_RemoteChessPT.x;
					int nPosY = m_RemoteChessPT.y;
					if (nPosX > -1 && nPosY > -1)
					{
						m_NodeList[nPosX][nPosY].m_Color = ncUNKOWN;
						NODE *pNode = new NODE();
						memcpy(pNode,&m_NodeList[nPosX][nPosY],sizeof(NODE));
						m_BackPlayList.AddTail(pNode);
						//ˢ�´���
						Invalidate();
					}
					m_IsDown = FALSE;
				}
				else	//�öԷ������ˣ���Ҫ��������
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
					//ˢ�´���
					Invalidate();
				}
				m_LocalChessPT.x  = -1;
				m_LocalChessPT.y  = -1;
				m_RemoteChessPT.x = -1;
				m_RemoteChessPT.y = -1;
			}
			else		//�ܾ�����
			{
				tcpPackage.cmdType = CT_BACKDENY;
				m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));	
			}
		}
		else if (tcpPackage.cmdType == CT_DRAWCHESSACCEPTANCE)	//�Է����պ�������
		{
			CSrvFiveChessDlg *pDlg = (CSrvFiveChessDlg*)GetParent();
			//���к��崦����Ϸ����
			m_TestNum = 0;

			m_IsDown = FALSE;
			m_IsStart = FALSE;
			m_IsWin = FALSE;
			m_State = esEND;
			InitializeNode();
			//���½���
			Invalidate();
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;	
			MessageBox("�Է�ͬ�����!","��ʾ");
		
		}
		else if (tcpPackage.cmdType == CT_DRAWCHESSDENY)	//�Է��ܾ�����
		{
			MessageBox("�Է��ܾ��˺���!","��ʾ");
		}
		else if (tcpPackage.cmdType == CT_DRAWCHESSREQUEST)	//�Է�������������
		{
			CSrvFiveChessDlg *pDlg = (CSrvFiveChessDlg*)GetParent();
			if (MessageBox("�Է�Ҫ����壬�Ƿ�ͬ�����?","��ʾ",MB_YESNO)==IDYES)
			{		//ͬ�����
				tcpPackage.cmdType = CT_DRAWCHESSACCEPTANCE;
				m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));
				
				//���к��崦����Ϸ����
				m_TestNum = 0;

				m_IsDown = FALSE;
				m_IsStart = FALSE;
				m_IsWin = FALSE;
				m_State = esEND;
				InitializeNode();
				//���½���
				Invalidate();
				m_LocalChessPT.x = m_LocalChessPT.y = -1;
				m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;
			}
			else	//�ܾ�����
			{
				tcpPackage.cmdType = CT_DRAWCHESSDENY;
				m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));		
			
			}
		}
		else if (tcpPackage.cmdType == CT_GIVEUP)			//�Է�������
		{
			CSrvFiveChessDlg *pDlg = (CSrvFiveChessDlg*)GetParent();
			//������Ϸ
			m_TestNum = 0;

			m_IsDown = FALSE;
			m_IsStart = FALSE;
			m_IsWin = FALSE;
			m_State = esEND;
			InitializeNode();
			//���½���
			Invalidate();
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;

			MessageBox("����ʤ��!","��ʾ");
		}
	}
	delete []pBuffer;
}

void CChessBorad::AcceptConnection()
{
	m_ClientSock.Close();
	m_SrvSock.Accept(m_ClientSock);
	m_IsConnect = TRUE;
	CSrvFiveChessDlg * pDlg = (CSrvFiveChessDlg*)GetParent();
	CTime tmNow = CTime::GetCurrentTime();
	CString csFormat = tmNow.Format("%H:%M:%S");
	pDlg->m_RightPanel.m_UserList.SetItemText(0,2,csFormat);
	//��ȡ�ͻ�����Ϣ
	CString csClientIP;
	UINT nPort;
	m_ClientSock.GetSockName(csClientIP,nPort);
	if (pDlg->m_RightPanel.m_UserList.GetItemCount()<2)
	{
		int nItem = pDlg->m_RightPanel.m_UserList.InsertItem(1,"");
		pDlg->m_RightPanel.m_UserList.SetItemText(nItem,1,csClientIP);
		pDlg->m_RightPanel.m_UserList.SetItemText(nItem,2,csFormat);
	}
	else
	{
		pDlg->m_RightPanel.m_UserList.SetItemText(1,1,csClientIP);
		pDlg->m_RightPanel.m_UserList.SetItemText(1,2,csFormat);		
	}
	pDlg->m_RightPanel.m_NetState.SetWindowText("��·״̬:������");
}

void CChessBorad::OnTimer(UINT nIDEvent) 
{
	if (m_IsConnect)
	{
		TCP_PACKAGE tcpPackage;
		tcpPackage.cmdType = CT_NETTEST;
		m_ClientSock.Send(&tcpPackage,sizeof(TCP_PACKAGE));		//�������������Ϣ
		m_TestNum++;
		if (m_TestNum > 3)	//�Է����ߣ���Ϸ����
		{
			m_TestNum = 0;
			m_IsDown = FALSE;
			m_IsStart = FALSE;
			m_IsWin = FALSE;
			m_State = esEND;
			m_IsConnect = FALSE;
			InitializeNode();
			CSrvFiveChessDlg * pDlg = (CSrvFiveChessDlg*)GetParent();
			pDlg->m_RightPanel.m_NetState.SetWindowText("��·״̬:�Ͽ�����");
			//���½���
			Invalidate();
			m_LocalChessPT.x = m_LocalChessPT.y = -1;
			m_RemoteChessPT.x = m_RemoteChessPT.y  = -1;
		}
	}	
	CDialog::OnTimer(nIDEvent);
}

void CChessBorad::Start()
{
	if (m_IsStart == FALSE)
	{
		m_IsStart = TRUE;
		InitializeNode();
	}
}

void CChessBorad::OnMenuSvrSetting()
{
	CServerSetting SrvDlg;
	if (m_ConfigSrv == FALSE)	//û�����÷�����
	{
		if (SrvDlg.DoModal()==IDOK)
		{
			UINT port = SrvDlg.m_Port;
			
			CSrvFiveChessDlg * pDlg = (CSrvFiveChessDlg*)GetParent();

			if (m_SrvSock.Create(port,SOCK_STREAM,SrvDlg.m_HostIP) && m_SrvSock.Listen())
			{
				m_ConfigSrv = TRUE;

				int nItem = pDlg->m_RightPanel.m_UserList.InsertItem(0,"");
				if (SrvDlg.m_NickName.IsEmpty())
					SrvDlg.m_NickName = "����";
				pDlg->m_RightPanel.m_UserList.SetItemText(nItem,0,SrvDlg.m_NickName);
				pDlg->m_RightPanel.m_UserList.SetItemText(nItem,1,SrvDlg.m_HostIP);
	
				CString csUser = "\r\n�ǳ�:";
				csUser += SrvDlg.m_NickName;
				csUser += "\r\n";
				csUser += "IP:";
				csUser += SrvDlg.m_HostIP;
				pDlg->m_RightPanel.m_User.SetWindowText(csUser);
				MessageBox("���������óɹ�!","��ʾ");
			}
			else
			{
				m_ConfigSrv = FALSE;
				MessageBox("����������ʧ��!","��ʾ");
			}
		}	//�Ի������
	}
	else
	{
		MessageBox("�Ѿ������˷�������Ϣ!","��ʾ");
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

//��Ϸ�ط�
void CChessBorad::GamePlayBack()
{
	CDC* pDC = GetDC();
	CDC memDC;
	CBitmap BmpWhite,BmpBlack,BmpBK;
	memDC.CreateCompatibleDC(pDC);
	BmpBlack.LoadBitmap(IDB_BLACK);
	BmpWhite.LoadBitmap(IDB_WHITE);
	BmpBK.LoadBitmap(IDB_BLANK);
	//��ȡλͼ��Ϣ
	BITMAP bmpInfo;
	BmpBlack.GetBitmap(&bmpInfo);
	int nBmpWidth = bmpInfo.bmWidth;
	int nBmpHeight = bmpInfo.bmHeight;
	POSITION pos = NULL;

	m_bBackPlay = FALSE;
	InitBackPlayNode();
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
			//�������̵ľֲ����
			//���Ȼ�ȡ���ĵ�����
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

		//��ʱ
		SYSTEMTIME beginTime,endTime;
		GetSystemTime(&beginTime);	
		if (beginTime.wSecond > 58)
			beginTime.wSecond = 58;
		
		while (true)		//������ʱ����
		{
			MSG msg;		//�ڻطŹ�������Ӧ�������
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

	MessageBox("��Ϸ�طŽ���!","��ʾ");

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
