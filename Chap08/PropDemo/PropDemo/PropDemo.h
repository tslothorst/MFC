
// PropDemo.h : main header file for the PropDemo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPropDemoApp:
// See PropDemo.cpp for the implementation of this class
//

class CPropDemoApp : public CWinApp
{
public:
	CPropDemoApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPropDemoApp theApp;
