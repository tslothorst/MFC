
// HexDump.h : main header file for the HexDump application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHexApp:
// See HexDump.cpp for the implementation of this class
//

class CHexApp : public CWinApp
{
public:
	CHexApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHexApp theApp;
