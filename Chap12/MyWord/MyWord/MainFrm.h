
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "StyleBar.h"

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
	CStyleBar m_wndStyleBar;
	CToolBar m_wndToolBar;
	CStatusBar m_wndStatusBar;

// Generated message map functions
protected:
	BOOL CreateToolBar();
	BOOL CreateStyleBar();
	BOOL CreateStatusBar();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()


	afx_msg void OnClose();
};


