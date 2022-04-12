
// MyWordView.h : interface of the CMyWordView class
//

#pragma once

class CMyWordCntrItem;

class CMyWordView : public CRichEditView
{
protected: // create from serialization only
	CMyWordView() noexcept;
	DECLARE_DYNCREATE(CMyWordView)

// Attributes
public:
	CMyWordDoc* GetDocument() const;

// Operations
public:
	void GetFontInfo(LPTSTR pszFaceName, int& nSize);
	void ChangeFont(LPCTSTR pszFaceName);
	void ChangeFontSize(int nSize);
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMyWordView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnCharBold();
	afx_msg void OnCharItalic();
	afx_msg void OnCharUnderline();
	afx_msg void OnParaLeft();
	afx_msg void OnParaCenter();
	afx_msg void OnParaRight();
	afx_msg void OnUpdateCharBold(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCharItalic(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCharUnderline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParaLeft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParaCenter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateParaRight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineNumber(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in MyWordView.cpp
inline CMyWordDoc* CMyWordView::GetDocument() const
   { return reinterpret_cast<CMyWordDoc*>(m_pDocument); }
#endif

