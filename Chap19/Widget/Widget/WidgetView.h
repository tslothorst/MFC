
// WidgetView.h : interface of the CWidgetView class
//

#pragma once

typedef struct tagWIDGETINFO {
	int x;		// x coordinate of the widget's upper left corner
	int y;		// y coordinate of the widget's upper left corner
	int cx;		// Horizontal drag offset
	int cy;		// Vertical drag offset
	COLORREF color;
} WIDGETINFO;

class CWidgetView : public CScrollView
{
protected: // create from serialization only
	CWidgetView() noexcept;
	DECLARE_DYNCREATE(CWidgetView)

// Attributes
public:
	CWidgetDoc* GetDocument() const;

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
	virtual ~CWidgetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CWidget* m_pTempWidget;
	CSize m_offset;
	CPoint m_pointLastImage;
	CPoint m_pointLastMsg;
	int m_nSel;
	COleDropTarget m_oleDropTarget;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in WidgetView.cpp
inline CWidgetDoc* CWidgetView::GetDocument() const
   { return reinterpret_cast<CWidgetDoc*>(m_pDocument); }
#endif

