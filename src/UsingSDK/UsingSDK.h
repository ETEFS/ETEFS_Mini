

#pragma once

#ifndef __AFXWIN_H__
	#error "errpt"
#endif

#include "resource.h"		



class CUsingSDKApp : public CWinAppEx
{
public:
	CUsingSDKApp();


	public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};

extern CUsingSDKApp theApp;