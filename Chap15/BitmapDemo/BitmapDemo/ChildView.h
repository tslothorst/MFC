
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "MaskedBitmap.h"


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnOptionsDrawOpaque();
	afx_msg void OnOptionsDrawTransparent();
	afx_msg void OnUpdateOptionsDrawOpaque(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsDrawTransparent(CCmdUI* pCmdUI);
	void DoGradientFill(CDC* pDC, LPRECT pRect);
	CPalette m_palette;
	CMaskedBitmap m_bitmap;
	BOOL m_bDrawOpaque;
};

