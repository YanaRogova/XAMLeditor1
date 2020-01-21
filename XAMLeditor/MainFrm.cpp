#include "pch.h"
#include "framework.h"
#include "XAMLeditor.h"
#include <string>
#include <fstream>
#include <iostream>

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_BUTTON, &CMainFrame::OnClickButton)
	
	
END_MESSAGE_MAP()

CMainFrame::CMainFrame() noexcept {}

CMainFrame::~CMainFrame() {}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CString str;
	str.LoadString(IDS_BUTTON_CONVERTER);
	m_wndButton.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		CRect(0, 0, 200, 100), this, ID_BUTTON);
	str.LoadString(IDS_STATIC);
	m_wndStatic.Create(str, WS_VISIBLE | WS_CHILD,
		CRect(2, 110, 150, 130), this, ID_STATIC);

	m_wndStaticX.Create(_T("X:"), WS_VISIBLE | WS_CHILD,
		CRect(2, 140, 17, 160), this, ID_STATIC_X);
	m_wndEditX.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_TABSTOP,
		CRect(20, 140, 130, 160), this, ID_EDIT_X);

	m_wndStaticY.Create(_T("Y:"), WS_VISIBLE | WS_CHILD,
		CRect(2, 170, 17, 190), this, ID_STATIC_Y);
	m_wndEditY.Create(WS_VISIBLE | WS_CHILD | ES_NUMBER | WS_TABSTOP,
		CRect(20, 170, 130, 190), this, ID_EDIT_Y);

	str.LoadString(IDS_DEBAG);
	m_wndCheckbox.Create(str, WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTOCHECKBOX,
		CRect(5, 200, 80, 220), this, ID_CHECKBOX);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

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
	ConvertXamlFiles();
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetWindowRect(&rect);
    ScreenToClient(&rect);
    pDC->FillSolidRect(rect, RGB(245, 245, 245));
    return TRUE;
}


void CMainFrame::ConvertXamlFiles()
{
	int iBufferSize = 100000;
	CFileDialog dlg(TRUE, NULL, _T("*.xaml"), OFN_ALLOWMULTISELECT |
		OFN_NOVALIDATE, _T("XAML vector icon (*.xaml)|*.xaml|"));
	int result = dlg.DoModal();
	if (result == IDOK)
	{
		POSITION ps = dlg.GetStartPosition();
		while (ps)
		{
			if (!EditXamlFile(dlg.GetNextPathName(ps)))
			{
				AfxMessageBox(_T("Error! File ") + dlg.GetPathName() + _T(" don't open."));
				return;
			}
		}
		AfxMessageBox(_T("Файл(ы) успешно конвертирован(ы)."));
	}
}

bool CMainFrame::EditXamlFile(CString name, bool isDeleted, char prefix)
{
	CString tempName = name;
	tempName.Insert(tempName.GetLength() - 5, prefix);

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
		if (m_wndCheckbox.GetCheck())
		{
			while (workString.find("#FFFFFFFF") != std::string::npos)
			{
				int index = workString.find("#FFFFFFFF");
				workString.erase(index, 9);
				workString.insert(index, "#FF23FC7F");
			}
			while (workString.find("#FFFFFF\"") != std::string::npos)
			{
				int index = workString.find("#FFFFFF\"");
				workString.erase(index, 7);
				workString.insert(index, "#23FC7F");
			}
			while (workString.find("#FFFFFF\'") != std::string::npos)
			{
				int index = workString.find("#FFFFFF\'");
				workString.erase(index, 7);
				workString.insert(index, "#23FC7F");
			}
		}
		newFile << workString << std::endl;
	}
	newFile.close();
	file.close();
	return true;
}



