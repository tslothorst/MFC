
// AutoMathView.h : interface of the CAutoMathView class
//

#pragma once


class CAutoMathView : public CView
{
protected: // create from serialization only
	CAutoMathView() noexcept;
	DECLARE_DYNCREATE(CAutoMathView)

// Attributes
public:
	CAutoMathDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CAutoMathView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AutoMathView.cpp
inline CAutoMathDoc* CAutoMathView::GetDocument() const
   { return reinterpret_cast<CAutoMathDoc*>(m_pDocument); }
#endif

