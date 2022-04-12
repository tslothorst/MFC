
// ScrollDemoView.h : interface of the CScrollDemoView class
//

#pragma once


class CScrollDemoView : public CScrollView
{
protected: // create from serialization only
	CScrollDemoView() noexcept;
	DECLARE_DYNCREATE(CScrollDemoView)

// Attributes
public:
	CScrollDemoDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CScrollDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

protected:
	BOOL m_bSmooth;
	void GetCellRect(int row, int col, LPRECT pRect);
	void DrawAddress(CDC* pDC, int row, int col);
	void DrawPointer(CDC* pDC, int row, int col, BOOL bHighlight);
	CFont m_font;
	int m_CurrentCol;
	int m_CurrentRow;
	int m_nRibbonWidth;
	int m_nCellHeight;
	int m_nCellWidth;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in ScrollDemoView.cpp
inline CScrollDemoDoc* CScrollDemoView::GetDocument() const
   { return reinterpret_cast<CScrollDemoDoc*>(m_pDocument); }
#endif

