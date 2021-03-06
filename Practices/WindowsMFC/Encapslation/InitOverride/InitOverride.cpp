// InitOverride.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

//定义全局变量和函数------------------------------------------------------------------------
HINSTANCE hInst;								
HINSTANCE hInstance;
MSG msg;
char lpszClassName[]="window_class";
char*ShowText;
//声明函数原型--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//窗口函数
void OnLButtonDown(HWND hWnd, UINT message, 
				WPARAM wParam, LPARAM lParam);
void OnPaint(HWND hWnd, UINT message, 
				WPARAM wParam, LPARAM lParam);
void OnDestroy(HWND hWnd, UINT message, 
				WPARAM wParam, LPARAM lParam);
//窗口类-----------------------------------------------------------------------------------------
class CFrameWnd
{		
public:	
	HWND hWnd;
public:
	int RegisterWindow();	
	void Create(LPCTSTR lpClassName,
				LPCTSTR lpWindowName
				);	
	void ShowWindow(int nCmdShow);
	void UpdateWindow();
};
//窗口类的成员函数---------------------------------------------------------------------------
int CFrameWnd::RegisterWindow()
{	
	WNDCLASS wc;
	wc.style=0;
	wc.lpfnWndProc=WndProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName=NULL;
	wc.lpszClassName=lpszClassName;
	return RegisterClass(&wc);
}
void CFrameWnd::Create(LPCTSTR lpClassName,
					   LPCTSTR lpWindowName)
{
	RegisterWindow( );
	hInst = hInstance; 
	hWnd = CreateWindow(lpszClassName,
						lpWindowName, 
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, 
						0, 
						CW_USEDEFAULT, 
						0, 
						NULL, 
						NULL, 
						hInstance, 
						NULL);
}
void CFrameWnd::ShowWindow(int nCmdShow)
{
	::ShowWindow(hWnd, nCmdShow);
}
void CFrameWnd::UpdateWindow()
{
	::UpdateWindow(hWnd);
}

//应用程序类----------------------------------------------------------------------------------
class CWinApp
{	
public:
	CFrameWnd*m_pMainWnd;
	CWinApp* m_pCurrentApp;//定义指针
public:
	virtual BOOL InitInstance (int nCmdShow);//虚函数
	int Run();
	CWinApp();//在构造函数中取得指针
	~CWinApp();
};
//应用程序类的成员函数-------------------------------------------------------------------
CWinApp::CWinApp()
{m_pCurrentApp = this;}//在构造函数中给指针赋值

BOOL CWinApp::InitInstance(int nCmdShow)
{
	m_pMainWnd=new CFrameWnd;
	m_pMainWnd->Create(NULL,"封装的Windows程序");
	m_pMainWnd->ShowWindow(nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}
int CWinApp::Run()
{
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
CWinApp::~CWinApp(){delete m_pMainWnd;}
//由CWinApp类派生CMyApp类------------------------------------------------------
class CMyApp:public CWinApp
{
public:
	BOOL InitInstance(int nCmdShow);//重新定义InitInstance函数
	
};
//重新定义的成员函数InitInstance --------------------------------------------------------
CMyApp::InitInstance(int nCmdShow)
{
	m_pMainWnd=new CFrameWnd;
	m_pMainWnd->Create(NULL,"用新的InitInstance函数的程序");
	m_pMainWnd->ShowWindow(nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}




//程序员定义的MyApp的对象theApp----------------------------------------------------
CMyApp theApp;

//定义全局函数AfxGetApp----------------------------------------------------
CWinApp* AfxGetApp()
{
	return theApp.m_pCurrentApp;
}

//主函数------------------------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE 	hInstance,
                     HINSTANCE 		hPrevInstance,
                     LPSTR     		lpCmdLine,
                     int       			nCmdShow)
{
	CWinApp* pApp;
	pApp = AfxGetApp();
	int ResultCode=-1;
	theApp.InitInstance(nCmdShow);
	return ResultCode=theApp.Run();
}
//窗口函数的实现--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_LBUTTONDOWN:	OnLButtonDown(hWnd, message, wParam, lParam);	
		break;
	case WM_PAINT:			OnPaint(hWnd, message,wParam, lParam);
		break;
	case WM_DESTROY:		OnDestroy(hWnd, message, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
void OnLButtonDown(HWND hWnd, UINT message, 
				WPARAM wParam, LPARAM lParam)
{
	ShowText="Hello!";
	InvalidateRect(hWnd,NULL,1);
}
void OnPaint(HWND hWnd, UINT message, 
				WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	TextOut(hdc,50,50,ShowText,6);
	EndPaint(hWnd, &ps);
}
void OnDestroy(HWND hWnd, UINT message, 
				WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
}
//-------------------------------------------------------------------------------------------




