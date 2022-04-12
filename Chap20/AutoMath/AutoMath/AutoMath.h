
// AutoMath.h : main header file for the AutoMath application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CAutoMathApp:
// See AutoMath.cpp for the implementation of this class
//

class CAutoMathApp : public CWinApp
{
public:
	CAutoMathApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAutoMathApp theApp;
