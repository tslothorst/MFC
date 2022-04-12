
// MyPad.h : main header file for the MyPad application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMyPadApp:
// See MyPad.cpp for the implementation of this class
//

class CMyPadApp : public CWinApp
{
public:
	CMyPadApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyPadApp theApp;
