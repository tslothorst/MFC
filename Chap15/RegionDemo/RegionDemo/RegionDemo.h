
// RegionDemo.h : main header file for the RegionDemo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRegionDemoApp:
// See RegionDemo.cpp for the implementation of this class
//

class CMyApp : public CWinApp 
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd 
{
public:
	CMainWindow();

protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};
