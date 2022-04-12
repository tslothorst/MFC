
// SdiSquaresView.h : interface of the CSdiSquaresView class
//

#pragma once


class CSdiSquaresView : public CView
{
protected: // create from serialization only
	CSdiSquaresView() noexcept;
	DECLARE_DYNCREATE(CSdiSquaresView)

// Attributes
public:
	CSdiSquaresDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CSdiSquaresView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in SdiSquaresView.cpp
inline CSdiSquaresDoc* CSdiSquaresView::GetDocument() const
   { return reinterpret_cast<CSdiSquaresDoc*>(m_pDocument); }
#endif

