
// VistaView.h : interface of the CVistaView class
//

#pragma once


class CVistaView : public CScrollView
{
protected: // create from serialization only
	CVistaView() noexcept;
	DECLARE_DYNCREATE(CVistaView)

// Attributes
public:
	CVistaDoc* GetDocument() const;

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
	virtual ~CVistaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VistaView.cpp
inline CVistaDoc* CVistaView::GetDocument() const
   { return reinterpret_cast<CVistaDoc*>(m_pDocument); }
#endif

