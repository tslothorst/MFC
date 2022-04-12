
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
	static const COLORREF m_clrColors[5];

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
	int m_nColor;
	int m_nShape;
	afx_msg void OnPaint();
	afx_msg void OnShapeCircle();
	afx_msg void OnShapeTriangle();
	afx_msg void OnShapeSquare();
	afx_msg void OnUpdateShapeCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShapeTriangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShapeSquare(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnColor(UINT nID);
	afx_msg void OnUpdateColor(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

