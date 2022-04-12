
// MdiSquaresView.h : interface of the CMdiSquaresView class
//

#pragma once


class CMdiSquaresView : public CView
{
protected: // create from serialization only
	CMdiSquaresView() noexcept;
	DECLARE_DYNCREATE(CMdiSquaresView)

// Attributes
public:
	CMdiSquaresDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMdiSquaresView();
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

#ifndef _DEBUG  // debug version in MdiSquaresView.cpp
inline CMdiSquaresDoc* CMdiSquaresView::GetDocument() const
   { return reinterpret_cast<CMdiSquaresDoc*>(m_pDocument); }
#endif

