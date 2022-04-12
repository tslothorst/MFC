
// DriveTree.h : main header file for the DriveTree application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDriveTreeApp:
// See DriveTree.cpp for the implementation of this class
//

class CDriveTreeApp : public CWinApp
{
public:
	CDriveTreeApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDriveTreeApp theApp;
