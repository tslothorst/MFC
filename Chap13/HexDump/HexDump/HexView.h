
// HexView.h : interface of the CHexView class
//

#pragma once


class CHexView : public CScrollView
{
protected: // create from serialization only
	CHexView() noexcept;
	DECLARE_DYNCREATE(CHexView)

// Attributes
public:
	CHexDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CHexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void FormatLine(CHexDoc* pDoc, UINT nLine, CString& string);
	void PrintPageHeader(CHexDoc* pDoc, CDC* pDC, UINT nPageNumber);
	void PrintPage(CHexDoc* pDoc, CDC* pDC, UINT nPageNumber);
	UINT m_cxWidth;
	UINT m_cxOffset;
	UINT m_nLinesPerPage;
	UINT m_nLinesTotal;
	UINT m_cyPrinter;
	UINT m_cyScreen;
	CFont m_fontPrinter;
	CFont m_fontScreen;
	DECLARE_MESSAGE_MAP()	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in HexView.cpp
inline CHexDoc* CHexView::GetDocument() const
   { return reinterpret_cast<CHexDoc*>(m_pDocument); }
#endif

