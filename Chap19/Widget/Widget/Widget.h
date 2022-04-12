
// Widget.h : main header file for the Widget application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CWidgetApp:
// See Widget.cpp for the implementation of this class
//

class CWidgetApp : public CWinApp
{
public:
	UINT GetClipboardFormat();
	CWidgetApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
protected:
	UINT m_nFormat;
};

extern CWidgetApp theApp;
