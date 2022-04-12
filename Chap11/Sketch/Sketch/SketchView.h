
// SketchView.h : interface of the CSketchView class
//

#pragma once


class CSketchView : public CScrollView
{
protected: // create from serialization only
	CSketchView() noexcept;
	DECLARE_DYNCREATE(CSketchView)

// Attributes
public:
	CSketchDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CSketchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void InvertLine(CDC* pDC, POINT from, POINT to);
	CPoint m_ptFrom;
	CPoint m_ptTo;
	HCURSOR m_hCursor;
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in SketchView.cpp
inline CSketchDoc* CSketchView::GetDocument() const
   { return reinterpret_cast<CSketchDoc*>(m_pDocument); }
#endif

