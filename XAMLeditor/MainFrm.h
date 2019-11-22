
// MainFrm.h: интерфейс класса CMainFrame
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // создать только из сериализации
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CMainFrame();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	CMFCCaptionBar    m_wndCaptionBar;
	CButton		      m_wndButton;
	CEdit			  m_wndEditX;
	CEdit			  m_wndEditY;
	CStatic           m_wndStatic;
	CStatic           m_wndStaticX;
	CStatic           m_wndStaticY;
// Созданные функции схемы сообщений
protected:
	afx_msg void OnClickButton();
	afx_msg void OnFileOpen();
	afx_msg bool EditXamlFile(std::string name, bool isDeleted, char prefix);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};
