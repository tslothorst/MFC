
// Wanderer.h : main header file for the Wanderer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CWandererApp:
// See Wanderer.cpp for the implementation of this class
//

class CWandererApp : public CWinApp
{
public:
	CWandererApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWandererApp theApp;
