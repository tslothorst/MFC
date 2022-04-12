
// ScrollDemo.h : main header file for the ScrollDemo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CScrollDemoApp:
// See ScrollDemo.cpp for the implementation of this class
//

class CScrollDemoApp : public CWinApp
{
public:
	CScrollDemoApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CScrollDemoApp theApp;
