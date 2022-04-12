
// ImageEdit.h : main header file for the ImageEdit application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CImageEditApp:
// See ImageEdit.cpp for the implementation of this class
//

class CImageEditApp : public CWinApp
{
public:
	CImageEditApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageEditApp theApp;
