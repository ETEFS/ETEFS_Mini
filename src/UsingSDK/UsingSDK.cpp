

#include "stdafx.h"
#include "UsingSDK.h"
#include "UsingSDKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUsingSDKApp

BEGIN_MESSAGE_MAP(CUsingSDKApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()




CUsingSDKApp::CUsingSDKApp()
{

}




CUsingSDKApp theApp;




BOOL CUsingSDKApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();


	CUsingSDKDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	
	}
	else if (nResponse == IDCANCEL)
	{
		
	}
	
	return FALSE;
}
