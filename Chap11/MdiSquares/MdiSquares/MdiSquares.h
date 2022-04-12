
// MdiSquares.h : main header file for the MdiSquares application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMdiSquaresApp:
// See MdiSquares.cpp for the implementation of this class
//

class CMdiSquaresApp : public CWinApp
{
public:
	CMdiSquaresApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMdiSquaresApp theApp;
