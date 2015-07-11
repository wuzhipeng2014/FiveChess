// ClientFiveChess.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ClientFiveChess.h"
#include "ClientFiveChessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientFiveChessApp
//定义按钮状态
enum ButtonState  {bsNormal,bsHot,bsDown};
//按钮包装类
class CDrawButton  
{
public:
	ButtonState m_State;           //按钮当前状态
	WNDPROC     m_OldProc;         //记录按钮的窗口函数
	int         m_Flag;            //是否释放关联按钮的CDrawButton对象
	static int  m_Style;           //按钮风格
public:

	CDrawButton( )
	{
		m_State   = bsNormal;
		m_OldProc = NULL;
		m_Flag    = 0;
	}

	virtual ~CDrawButton()
	{
		m_State   = bsNormal;
		m_OldProc = NULL;		
	};

	LRESULT OnPaint( HWND hWnd ) 
	{
		CWnd* pWnd = CWnd::FromHandle(hWnd);
		
		CPaintDC	dc(pWnd);
		CString		Text;
		CRect		RC;
		CFont		Font;
		CFont		*pOldFont;
		CBrush		Brush;
		CBrush		*pOldBrush;
		CPoint		PT(2,2);
		
		dc.SetBkMode( TRANSPARENT );
		Font.CreateFont( 12, 0, 0, 0, FW_HEAVY, 0, 0, 0, ANSI_CHARSET, \
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, \
			VARIABLE_PITCH | FF_SWISS, "MS Sans Serif" );

		pOldFont = dc.SelectObject( &Font );
		
		if( m_State == bsNormal)
		{
			
			if (m_Style==2)
			{
				CBitmap bmp;
				bmp.LoadBitmap(IDB_BKBUTTON);
				Brush.CreatePatternBrush(&bmp); 
			}
			else
				Brush.CreateSolidBrush( RGB( 200, 200, 200 ) );
			dc.SetTextColor( RGB( 80, 80, 80) );
		}
		else if( m_State == bsDown )
		{
			Brush.CreateSolidBrush( RGB( 160, 160, 160 ) );
			dc.SetTextColor( RGB( 50, 50, 250 ) );
		}
		else if( m_State == bsHot )
		{
			Brush.CreateSolidBrush( RGB( 100, 100, 180 ) );
			dc.SetTextColor( RGB( 250, 250, 0 ) );
		}
		
		pOldBrush = dc.SelectObject( &Brush );
		pWnd->GetClientRect( &RC );
		dc.RoundRect( &RC, PT );
		
		HRGN hRgn = CreateRectRgn( RC.left, RC.top, RC.right, RC.bottom );
		pWnd->SetWindowRgn( hRgn, TRUE );
		DeleteObject( hRgn );
		
		pWnd->GetWindowText(Text );
		dc.DrawText( Text, &RC, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		
		dc.SelectObject( pOldFont );
		dc.SelectObject( pOldBrush );
		
		return TRUE;
	}
	LRESULT OnLButtonDown( HWND hWnd, UINT nFlags, CPoint point )
	{
		m_State = bsDown;		
		SetCapture(hWnd);
		SetFocus(hWnd);
		return TRUE;
	}
	
	LRESULT OnLButtonUp( HWND hWnd, UINT nFlags, CPoint point )
	{
		if( m_State != bsNormal )
		{
			m_State = bsNormal;
			ReleaseCapture();
			InvalidateRect(hWnd,NULL,TRUE);
			SendMessage( GetParent(hWnd), WM_COMMAND, GetDlgCtrlID(hWnd), (LPARAM) (hWnd) );
		}
		return TRUE;
	}

	LRESULT LoseFocus(HWND  hWnd)
	{
		m_State = bsNormal;
		InvalidateRect(hWnd,NULL,TRUE);
		SendMessage( hWnd, WM_KILLFOCUS, (long)hWnd, 0);	
		return TRUE;
	}

	LRESULT OnMouseMove(HWND hWnd, UINT nFlags, CPoint point ) {
		HRGN hRgn = CreateRectRgn( 0, 0, 0, 0 );
		GetWindowRgn( hWnd,hRgn );
		BOOL ret = PtInRegion( hRgn, point.x, point.y );
		if( ret ) 
		{
			
			if( m_State == bsDown) 
				return TRUE;
			if( m_State != bsHot ) 
			{
				m_State = bsHot;
				InvalidateRect(hWnd,NULL,TRUE);
				UpdateWindow(hWnd);
				SetCapture(hWnd);
			}
		} 
		else 
		{
			m_State = bsNormal;
			InvalidateRect(hWnd,NULL,TRUE);	
			ReleaseCapture();
		}	
		DeleteObject( hRgn );
		return TRUE;
	}
};

HHOOK  hWndHook ;
int CDrawButton::m_Style = 1;

LRESULT __stdcall DefWindowProc1(HWND hWnd,UINT Msg,WPARAM wParam, 
								 LPARAM lParam )
{
	CPoint pt;
	CDrawButton *pButton=(CDrawButton*)GetWindowLong(hWnd,GWL_USERDATA);
	switch (Msg)
	{
	case 0x0128:
	case WM_LBUTTONDBLCLK:  //屏蔽双击事件
		{
			return TRUE;
			break;
		}
		case WM_PAINT:
			{
				if (pButton->m_Style>0)
					return pButton->OnPaint( hWnd);
				else
					return  CallWindowProc(pButton->m_OldProc, hWnd,Msg,wParam,lParam);
				break;
			}
		case WM_LBUTTONDOWN:
			{
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				if (pButton->m_Style>0)
					return pButton->OnLButtonDown( hWnd, 0, pt );
				else
					return  CallWindowProc(pButton->m_OldProc, hWnd,Msg,wParam,lParam);
				break;
			}
		case WM_LBUTTONUP:
			{
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				if (pButton->m_Style>0)
					return pButton->OnLButtonUp( hWnd, 0,pt );
				else
					return  CallWindowProc(pButton->m_OldProc, hWnd,Msg,wParam,lParam);
				break;
			}
		case WM_MOUSEMOVE:
			{

				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				if (pButton->m_Style>0)
					return pButton->OnMouseMove(hWnd,0, pt);
				else
					return  CallWindowProc(pButton->m_OldProc, hWnd,Msg,wParam,lParam);

				break;
			}

		case WM_DESTROY:
			{				
			  	 WNDPROC procOld=pButton->m_OldProc;
				 SetWindowLong(hWnd,GWL_WNDPROC,(long)procOld); //恢复原来的窗口函数

				 CWnd* pWnd = ::CWnd::FromHandle(hWnd);  //将按钮对象与句柄分离
				 if (pWnd)
				 {
					pWnd->Detach();
				 }
				 pButton->m_Flag = 1;
				 return 1;//ret;
			}
		default :
			{
				break;
			}
	}
	return CallWindowProc(pButton->m_OldProc, hWnd, Msg, wParam, lParam );
}


//定义钩子函数
LRESULT CALLBACK HOOKProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	PCWPSTRUCT	wc = (PCWPSTRUCT) lParam;
	HWND  hWnd = wc->hwnd;
	if( hWnd ) 
	{
		char ClassName[MAX_PATH] = "";
		GetClassName( hWnd, ClassName, MAX_PATH );
		if( strcmp( ClassName, "Button" ) == 0 )
		{
			CWnd	*pWnd = CWnd::FromHandle( hWnd );

			if ( pWnd->GetStyle() & BS_RADIOBUTTON ||pWnd->GetStyle() & BS_CHECKBOX )
			{
				return 1;
			}

			WNDPROC	WndProc;
			WndProc = (WNDPROC) GetWindowLong( hWnd, GWL_WNDPROC );
			
			CDrawButton *pButton=(CDrawButton*)GetWindowLong(hWnd,GWL_USERDATA);

			if (pButton != NULL&& pButton->m_Flag==1 )
			{
				SetWindowLong(hWnd,GWL_USERDATA,0);
				SetWindowLong( hWnd, GWL_WNDPROC, (LONG)pButton->m_OldProc );

				pButton->m_OldProc = NULL;
				delete pButton;
			}
			else if (pButton == NULL ) 
			{
				if( WndProc !=DefWindowProc1 )
				{
					pButton = new CDrawButton;
					pButton->m_OldProc = WndProc;
					SetWindowLong(hWnd,GWL_USERDATA,(long)pButton);
					WndProc =  (WNDPROC) SetWindowLong( hWnd, GWL_WNDPROC, (LONG) DefWindowProc1);
				}
			}
		}
	}
	return CallNextHookEx( hWndHook, nCode, wParam, lParam );
}

//安装钩子
BOOL  RunHook( HMODULE hModule, DWORD dwThreadID)
{
	hWndHook = SetWindowsHookEx(
		WH_CALLWNDPROC, (HOOKPROC) HOOKProc, hModule, dwThreadID );
	return TRUE;
}

//卸载钩子
BOOL  StopHook()
{
	UnhookWindowsHookEx(hWndHook);
	return TRUE;
}



BEGIN_MESSAGE_MAP(CClientFiveChessApp, CWinApp)
	//{{AFX_MSG_MAP(CClientFiveChessApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientFiveChessApp construction

CClientFiveChessApp::CClientFiveChessApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClientFiveChessApp object

CClientFiveChessApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClientFiveChessApp initialization

BOOL CClientFiveChessApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	HINSTANCE hModule = GetModuleHandle( NULL );
	RunHook ( hModule, GetCurrentThreadId() );

	WSADATA wsa;
	AfxSocketInit(&wsa);

	CClientFiveChessDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CClientFiveChessApp::ExitInstance() 
{

	StopHook();		
	return CWinApp::ExitInstance();
}
