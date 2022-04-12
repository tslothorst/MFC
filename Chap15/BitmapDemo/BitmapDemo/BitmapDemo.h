
// BitmapDemo.h : main header file for the BitmapDemo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBitmapDemoApp:
// See BitmapDemo.cpp for the implementation of this class
//

class CBitmapDemoApp : public CWinApp
{
public:
	CBitmapDemoApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBitmapDemoApp theApp;
