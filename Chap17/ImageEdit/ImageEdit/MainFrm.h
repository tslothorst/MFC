
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "SpecialStatusBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CSpecialStatusBar          m_wndStatusBar;


// Generated message map functions
protected:
	int m_nPercentDone;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg LRESULT OnUpdateImageStats(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadFinished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnThreadAborted(WPARAM wParam, LPARAM lParam);
};


