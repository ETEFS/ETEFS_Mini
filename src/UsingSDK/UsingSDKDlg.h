
// UsingSDKDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CUsingSDKDlg 对话框
class CUsingSDKDlg : public CDialog, public IEventReceiver
{
// 构造
public:
	CUsingSDKDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_USINGSDK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	IFileEventServer*   m_FileEventServer;

// 实现
protected:
	HICON m_hIcon;
	DWORD  CUsingSDKDlg::OnFileEvent(PFILE_EVENT_PACKET  pFileEventPacket) ;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	BOOL      m_bStarted;
	afx_msg void OnBnClickedButtonLoadPolicy();
	afx_msg void OnBnClickedButtonUnloadPolicy();
protected:
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButton1();
};
