
// EZPrint.h : main header file for the EZPrint application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEZPrintApp:
// See EZPrint.cpp for the implementation of this class
//

class CEZPrintApp : public CWinApp
{
public:
	CEZPrintApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEZPrintApp theApp;
