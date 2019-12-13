#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "XAMLeditor.h"
#include "MainFrm.h"

#include "XAMLeditorDoc.h"
#include "XAMLeditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXAMLeditorApp

BEGIN_MESSAGE_MAP(CXAMLeditorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CXAMLeditorApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()



CXAMLeditorApp::CXAMLeditorApp() noexcept
{
	SetAppID(_T("XAMLeditor.AppID.NoVersion"));

}

CXAMLeditorApp theApp;

BOOL CXAMLeditorApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));
	LoadStdProfileSettings(0);

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CXAMLeditorDoc),
		RUNTIME_CLASS(CMainFrame), 
		RUNTIME_CLASS(CXAMLeditorView)); 
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	CMFCToolBar::m_bExtCharTranslation = TRUE;

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CXAMLeditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


CMsgDlg::CMsgDlg(CWnd* pParent)
	: CDialog(IDD_MSG_DIALOG, pParent)
{
}