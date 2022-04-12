
// DlgDemo1.h : main header file for the DlgDemo1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDlgDemo1App:
// See DlgDemo1.cpp for the implementation of this class
//

class CDlgDemo1App : public CWinApp
{
public:
	CDlgDemo1App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDlgDemo1App theApp;
