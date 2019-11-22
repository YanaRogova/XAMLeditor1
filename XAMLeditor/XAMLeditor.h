
// XAMLeditor.h: основной файл заголовка для приложения XAMLeditor
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы

#define ID_BUTTON1 1309
#define ID_BUTTON 1300
#define ID_EDIT_X  1301
#define ID_EDIT_Y  1302
#define ID_STATIC 1303
#define ID_STATIC_X 1304
#define ID_STATIC_Y 1305
#define ID_FILEDIALOG 1306
// CXAMLeditorApp:
// Сведения о реализации этого класса: XAMLeditor.cpp
//

class CXAMLeditorApp : public CWinApp
{
public:
	CXAMLeditorApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

protected:
};

extern CXAMLeditorApp theApp;
