
// LivePalette.h : main header file for the LivePalette application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

class CMyApp : public CWinApp 
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd 
{
protected:
	CPalette m_palette;
	void DoBkgnFill(CDC* pDC, LPRECT pRect);
	void DoDrawText(CDC* pDC, LPRECT pRect);

public:
	CMainWindow();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nTimerID);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};
