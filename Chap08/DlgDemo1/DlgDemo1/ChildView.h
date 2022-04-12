
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
	int m_nWidth;
	int m_nHeight;
	int m_nUnits;

	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOptions();
};

