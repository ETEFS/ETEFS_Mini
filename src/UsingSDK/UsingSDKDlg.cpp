
#include "stdafx.h"
#include "UsingSDK.h"
#include "UsingSDKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


CUsingSDKDlg::CUsingSDKDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUsingSDKDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUsingSDKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CUsingSDKDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_LOAD_POLICY, &CUsingSDKDlg::OnBnClickedButtonLoadPolicy)
	ON_BN_CLICKED(IDC_BUTTON_UNLOAD_POLICY, &CUsingSDKDlg::OnBnClickedButtonUnloadPolicy)
END_MESSAGE_MAP()



BOOL CUsingSDKDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_bStarted = FALSE;

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);	


	GetDlgItem(IDC_BUTTON_LOAD_POLICY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_UNLOAD_POLICY)->EnableWindow(FALSE);


	LONG lStyle,dwStyle;
	lStyle = GetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK;
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_ListCtrl.m_hWnd, GWL_STYLE, lStyle); 

	dwStyle = m_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_ListCtrl.SetExtendedStyle(dwStyle);

	m_ListCtrl.InsertColumn(0, _T("Event Name"),   LVCFMT_LEFT, 100);
	m_ListCtrl.InsertColumn(1, _T("Data"),       LVCFMT_LEFT, 280);

	BOOL  bStarted = FALSE;
	if( GetStartFiltering(&bStarted) != ERR_SUCCESS )
	{
		AfxMessageBox(_T("Cann't open minifilter driver,please reinstall ETEFS_Mini."));
		return TRUE;
	}

	return TRUE;  
}

void CUsingSDKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CUsingSDKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CUsingSDKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CUsingSDKDlg::OnBnClickedButtonLoadPolicy()
{
	{
		char  szKey[] = "0123456789012345";

		SetStartFiltering(TRUE);	
		SetDriverCryptConfig( CIPHER_ID_XTEA, szKey, 16 );
		SetRandomKeyMode(FALSE);
		SetCustomDataResident(1);


		LoadWordPolicy( );
		LoadExcelPolicy( );
		LoadNotepadPolicy();
		LoadPPTPolicy();
	}


	{
		CreateFileEventServer(&m_FileEventServer);
		m_FileEventServer->Startup( this);
	}


	{
		StartControlModule();
		SetEventReportValue(TRUE);
		SetPrivilegeControlValue(TRUE);
	}


	GetDlgItem(IDC_BUTTON_LOAD_POLICY)->EnableWindow( FALSE );
	GetDlgItem(IDC_BUTTON_UNLOAD_POLICY)->EnableWindow(TRUE);

	m_bStarted = TRUE;

}

void CUsingSDKDlg::OnBnClickedButtonUnloadPolicy()
{
	SetEventReportValue(FALSE);
	SetPrivilegeControlValue(FALSE);

	StopControlModule();

	UnloadNotepadPolicy();
	UnloadWordpadPolicy();
	UnloadPPTPolicy();

	SetStartFiltering(FALSE);

	delete m_FileEventServer;

	GetDlgItem(IDC_BUTTON_LOAD_POLICY)->EnableWindow( TRUE );
	GetDlgItem(IDC_BUTTON_UNLOAD_POLICY)->EnableWindow(FALSE);

	m_bStarted = FALSE;
}

void CUsingSDKDlg::OnCancel()
{
	if( m_bStarted )
	{
		AfxMessageBox(_T("Please unload polices."));
		return;
	}

	__super::OnCancel();
}


DWORD  CUsingSDKDlg::OnFileEvent(PFILE_EVENT_PACKET  pFileEventPacket) 
{

	int nItemCount = m_ListCtrl.GetItemCount();
	DWORD  dwRet = FE_SUCCESS;

	switch(pFileEventPacket->dwEventID )
	{
	case EVENT_ID_FILE_QUERY_PRIVILEGE:
		{
			BOOL  bUseCustomData = FALSE;

			pFileEventPacket->QueryPrivilege.Privilege.bDisableWrite  = FALSE;
			pFileEventPacket->QueryPrivilege.Privilege.bDisableCopyToClipboard = FALSE;
			pFileEventPacket->QueryPrivilege.Privilege.bDisableDrag = FALSE;
			pFileEventPacket->QueryPrivilege.Privilege.bDisableOpen = FALSE;
			pFileEventPacket->QueryPrivilege.Privilege.bDisablePrint = FALSE;
			pFileEventPacket->QueryPrivilege.Privilege.bDisableSaveAs = FALSE;

			pFileEventPacket->dwStatusCode = FE_SUCCESS;


			m_ListCtrl.InsertItem(nItemCount, L"QUERY_PRIVILEGE");
			m_ListCtrl.SetItemText(nItemCount, 1, pFileEventPacket->QueryPrivilege.wszSrcFileName);
		}
		break;

	case EVENT_ID_FILE_OPEN_FROM_API:
		{
			m_ListCtrl.InsertItem(nItemCount, L"OPEN_FROM_API");
			m_ListCtrl.SetItemText(nItemCount, 1, pFileEventPacket->FileOpenFromApi.wszSrcFileName);
		}
		break;


	case EVENT_ID_FILE_PRINT:
		{
			m_ListCtrl.InsertItem(nItemCount, L"PRINT");
			m_ListCtrl.SetItemText(nItemCount, 1, pFileEventPacket->FilePrint.wszSrcFileName);
		}
		break;

	default:
		{

		}
		break;

	}

	return dwRet;
}

