
// SdiSquares.h : main header file for the SdiSquares application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSdiSquaresApp:
// See SdiSquares.cpp for the implementation of this class
//

class CSdiSquaresApp : public CWinApp
{
public:
	CSdiSquaresApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSdiSquaresApp theApp;
