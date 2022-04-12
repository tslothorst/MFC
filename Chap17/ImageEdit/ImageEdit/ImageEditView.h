
// ImageEditView.h : interface of the CImageEditView class
//

#pragma once


class CImageEditView : public CScrollView
{
protected: // create from serialization only
	CImageEditView() noexcept;
	DECLARE_DYNCREATE(CImageEditView)

// Attributes
public:
	CImageEditDoc* GetDocument() const;

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
	virtual ~CImageEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageEditView.cpp
inline CImageEditDoc* CImageEditView::GetDocument() const
   { return reinterpret_cast<CImageEditDoc*>(m_pDocument); }
#endif

