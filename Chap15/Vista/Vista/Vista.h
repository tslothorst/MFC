
// Vista.h : main header file for the Vista application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CVistaApp:
// See Vista.cpp for the implementation of this class
//

class CVistaApp : public CWinApp
{
public:
	CVistaApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVistaApp theApp;
