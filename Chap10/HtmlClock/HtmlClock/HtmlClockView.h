
// HtmlClockView.h : interface of the CHtmlClockView class
//

#pragma once


class CHtmlClockView : public CHtmlView
{
protected: // create from serialization only
	CHtmlClockView() noexcept;
	DECLARE_DYNCREATE(CHtmlClockView)

// Attributes
public:
	CHtmlClockDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CHtmlClockView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* pDC);
public:
	virtual void OnTitleChange(LPCTSTR lpszText);
};

#ifndef _DEBUG  // debug version in HtmlClockView.cpp
inline CHtmlClockDoc* CHtmlClockView::GetDocument() const
   { return reinterpret_cast<CHtmlClockDoc*>(m_pDocument); }
#endif

