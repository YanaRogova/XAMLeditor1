#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"   

#define ID_BUTTON 1300
#define ID_EDIT_X  1301
#define ID_EDIT_Y  1302
#define ID_STATIC 1303
#define ID_STATIC_X 1304
#define ID_STATIC_Y 1305
#define ID_CHECKBOX 1306

class CXAMLeditorApp : public CWinApp
{
public:
	CXAMLeditorApp() noexcept;

public:
	virtual BOOL InitInstance();

	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CXAMLeditorApp theApp;

class CMsgDlg : public CDialog		// класс диалогового окна
{
public:
	CMsgDlg(CWnd* pParent = NULL);
};
