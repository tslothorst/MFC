
// GridDemo.h : main header file for the GridDemo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGridDemoApp:
// See GridDemo.cpp for the implementation of this class
//

class CGridDemoApp : public CWinApp
{
public:
	CGridDemoApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGridDemoApp theApp;
