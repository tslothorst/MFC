
// WandererView.h : interface of the CWandererView class
//

#pragma once


class CWandererView : public CView
{
protected: // create from serialization only
	CWandererView() noexcept;
	DECLARE_DYNCREATE(CWandererView)

// Attributes
public:
	CWandererDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CWandererView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WandererView.cpp
inline CWandererDoc* CWandererView::GetDocument() const
   { return reinterpret_cast<CWandererDoc*>(m_pDocument); }
#endif

