#pragma once
#include <afxwin.h>

class CMouseCapApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CFrameWnd
{
protected:
	BOOL m_bTracking;			// TRUE if rubberbanding
	BOOL m_bCaptureEnabled;		// TRUE if capture enabled
	CPoint m_ptFrom;			// "From" point for rubber banding
	CPoint m_ptTo;				// "To" point for rubber banding

	void InvertLine(CDC* pDC, CPoint ptFrom, CPoint ptTo);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	DECLARE_MESSAGE_MAP()

public:
	CMainWindow();
};