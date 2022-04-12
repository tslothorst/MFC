
// WinDir.h : main header file for the WinDir application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CWinDirApp:
// See WinDir.cpp for the implementation of this class
//

class CWinDirApp : public CWinApp
{
public:
	CWinDirApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWinDirApp theApp;
