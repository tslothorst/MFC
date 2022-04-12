
// Phones.h : main header file for the Phones application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPhonesApp:
// See Phones.cpp for the implementation of this class
//

class CPhonesApp : public CWinApp
{
public:
	CPhonesApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPhonesApp theApp;
