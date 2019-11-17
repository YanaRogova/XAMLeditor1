
// MainFrm.cpp: реализация класса CMainFrame
//

#include "pch.h"
#include "framework.h"
#include "XAMLeditor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_BUTTON, &CMainFrame::OnClickButton)
END_MESSAGE_MAP()

// Создание или уничтожение CMainFrame

CMainFrame::CMainFrame() noexcept
{
	// TODO: добавьте код инициализации члена
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	m_wndButton.Create(_T("Конвертировать файл"), WS_VISIBLE | WS_CHILD,
		CRect(0, 0, 200, 100), this, ID_BUTTON);

	m_wndStatic.Create(_T("Привести к размеру:"), WS_VISIBLE | WS_CHILD,
		CRect(2, 110, 150, 130), this, ID_STATIC);

	m_wndStaticX.Create(_T("X:"), WS_VISIBLE | WS_CHILD,
		CRect(2, 140, 17, 160), this, ID_STATIC_X);
	m_wndEditX.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER,
		CRect(20, 140, 130, 160), this, ID_EDIT_X);

	m_wndStaticY.Create(_T("Y:"), WS_VISIBLE | WS_CHILD,
		CRect(2, 170, 17, 190), this, ID_STATIC_Y);
	m_wndEditY.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER,
		CRect(20, 170, 130, 190), this, ID_EDIT_Y);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	cs.style = WS_BORDER | WS_CAPTION | FWS_ADDTOTITLE | WS_MINIMIZEBOX | WS_SYSMENU;

	RECT WndRect;
	WndRect.top = 0;
	WndRect.left = 0;
	WndRect.bottom = 400;
	WndRect.right = 600;
	AdjustWindowRectEx(&WndRect, cs.style, TRUE, cs.dwExStyle);
	cs.cx = WndRect.right - WndRect.left;
	cs.cy = WndRect.bottom - WndRect.top;
	return TRUE;
}

void CMainFrame::OnClickButton()
{
	//m_wndButton.OpenClipboard();

}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
	pDC->FillSolidRect(0, 0, 2000, 5000, RGB(245, 245, 245));
	return 0;
}

