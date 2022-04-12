
// HtmlClock.h : main header file for the HtmlClock application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHtmlClockApp:
// See HtmlClock.cpp for the implementation of this class
//

class CHtmlClockApp : public CWinApp
{
public:
	CHtmlClockApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHtmlClockApp theApp;
