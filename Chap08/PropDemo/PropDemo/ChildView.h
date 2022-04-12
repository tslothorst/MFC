
// ChildView.h : interface of the CChildView class
//


#pragma once


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
	int m_nUnits;
	int m_nHeight;
	int m_nWidth;
	int m_nColor;
	afx_msg void OnFileProperties();
	afx_msg LRESULT OnApply(WPARAM wParam, LPARAM lParam);
};

