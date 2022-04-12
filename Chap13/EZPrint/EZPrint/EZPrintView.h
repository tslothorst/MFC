
// EZPrintView.h : interface of the CEZPrintView class
//

#pragma once


class CEZPrintView : public CView
{
protected: // create from serialization only
	CEZPrintView() noexcept;
	DECLARE_DYNCREATE(CEZPrintView)

// Attributes
public:
	CEZPrintDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CEZPrintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in EZPrintView.cpp
inline CEZPrintDoc* CEZPrintView::GetDocument() const
   { return reinterpret_cast<CEZPrintDoc*>(m_pDocument); }
#endif

