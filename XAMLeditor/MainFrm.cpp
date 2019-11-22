
// MainFrm.cpp: реализация класса CMainFrame
//

#include "pch.h"
#include "framework.h"
#include "XAMLeditor.h"
#include <string>
#include <fstream>

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
	ON_COMMAND(ID_BUTTON1, &CMainFrame::OnFileOpen)
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
	CFileDialog dlg(true);
	dlg.DoModal();
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
	pDC->FillSolidRect(0, 0, 2000, 5000, RGB(245, 245, 245));
	return 0;
}




void CMainFrame::OnFileOpen()
{
	int iBufferSize = 100000;
	CFileDialog dlg(TRUE, NULL, _T("*.xaml"), OFN_ALLOWMULTISELECT |
		OFN_NOVALIDATE, _T("XAML vertex icon (*.xaml)|*.xaml|"));

	dlg.m_ofn.nMaxFile = iBufferSize;
	char* cNewBuffer = new char[iBufferSize];
	dlg.m_ofn.lpstrFile = cNewBuffer;
	dlg.m_ofn.lpstrFile[0] = NULL;
	int result = dlg.DoModal();
	if (result == IDOK)
	{
		POSITION ps = dlg.GetStartPosition();
		while (ps)
		{
			if (!EditXamlFile((std::string)dlg.GetNextPathName(ps)))
				AfxMessageBox(_T("Error! File ") + dlg.GetPathName() + _T(" don't open."));
		}
	}
	delete[]cNewBuffer;
}

bool CMainFrame::EditXamlFile(std::string name, bool isDeleted, char prefix)
{
	std::string tempName = name;
	tempName.insert(tempName.length() - 5, 1, prefix);

	std::ifstream file(name, std::ios_base::in);
	std::ofstream newFile(tempName, std::ios_base::out | std::ios_base::trunc);

	int counter = 0;
	std::string workString;

	if (!file.is_open() || !newFile.is_open())
	{
		return false;
	}

	while (!file.eof())
	{
		std::getline(file, workString);
		if ((workString.find("/Canvas") != std::string::npos))
		{
			if (counter == 1)
				workString = "</Viewbox>";
			else
			{
				while (workString.find("x:Name=") != std::string::npos)
					workString.erase(workString.find("x:Name="), 2);
			}

			counter--;
		}
		else if (workString.find("<Canvas") != std::string::npos)
		{
			if (counter == 0)
				workString = "<Viewbox xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\" Stretch=\"Uniform\">";
			else
			{
				while (workString.find("x:Name=") != std::string::npos)
					workString.erase(workString.find("x:Name="), 2);
			}

			counter++;
		}
		else
		{
			while (workString.find("x:Name=") != std::string::npos)
				workString.erase(workString.find("x:Name="), 2);
		}


		newFile << workString << std::endl;
	}

	file.close();

	if (isDeleted)
		remove(name.c_str());

	newFile.close();

	return true;
}