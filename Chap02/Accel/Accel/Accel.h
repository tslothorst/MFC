
#pragma once
#include <afxwin.h>


class CAccelApp : CWinApp 
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd
{
public:
	CMainWindow();	
protected:

	static constexpr int linesize = 8;

	int m_nCellWidth;	// Cell width in pixels
	int m_nCellHeight;	// Cell height in pixels
	int m_nRibbonWidth;	// Ribbon widht in pixels
	int m_nViewWidth;	// Workspace width in pixels
	int m_nViewHeight;	// Workspace height in pixels
	int m_nHScrollPos;	// Horizontal scroll position
	int m_nVScrollPos;	// Vertical scroll position
	int m_nHPageSize;	// Horizontal scroll position
	int m_nVPageSize;	// Vertical page size

	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nCode, UINT nPos, CScrollBar* pScrollbar);
	afx_msg void OnVScroll(UINT nCode, UINT nPos, CScrollBar* pScrollbar);

	DECLARE_MESSAGE_MAP()
};
