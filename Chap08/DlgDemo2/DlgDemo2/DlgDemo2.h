
// DlgDemo2.h : main header file for the DlgDemo2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDlgDemo2App:
// See DlgDemo2.cpp for the implementation of this class
//

class CDlgDemo2App : public CWinApp
{
public:
	CDlgDemo2App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDlgDemo2App theApp;
