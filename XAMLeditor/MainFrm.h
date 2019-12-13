#pragma once

class CMainFrame : public CFrameWnd
{
	
protected:
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

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
	CButton           m_wndCheckbox;
	CButton           m_wndButtonEN;
	CButton           m_wndButtonRU;
	
protected:
	afx_msg void OnClickButton();
	afx_msg void ConvertXamlFiles();
	afx_msg bool EditXamlFile(CString name, bool isDeleted = false, char prefix = 'N');
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//afx_msg void CMainFrame::English(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};
