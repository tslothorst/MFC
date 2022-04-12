
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "COptionsDialog.h"

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
	int m_nWidth;
	int m_nHeight;
	int m_nUnits;

protected:
	COptionsDialog* m_pDlg;

	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOptions();
	afx_msg LRESULT OnApply(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDialogDestroyed(WPARAM wParam, LPARAM lParam);
};

