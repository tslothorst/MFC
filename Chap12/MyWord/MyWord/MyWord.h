
// MyWord.h : main header file for the MyWord application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMyWordApp:
// See MyWord.cpp for the implementation of this class
//

class CMyWordApp : public CWinApp
{
public:
	CMyWordApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyWordApp theApp;
