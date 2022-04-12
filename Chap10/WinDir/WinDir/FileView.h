
// FileView.h : interface of the CFileView class
//

#pragma once

typedef struct tagITEMINFO {
	CString strFileName;
	DWORD nFileSizeLow;
	FILETIME ftLastWriteTime;
} ITEMINFO;

class CFileView : public CListView
{
protected: // create from serialization only
	CFileView() noexcept;
	DECLARE_DYNCREATE(CFileView)

// Attributes
public:
	CWinDirDoc* GetDocument() const;

// Operations
public:
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	int Refresh(LPCTSTR pszPath);
	virtual ~CFileView();
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
	CString m_strPath;
	void FreeItemMemory();
	BOOL AddItem(int nIndex, WIN32_FIND_DATA* pfd);
	CImageList m_ilSmall;
	CImageList m_ilLarge;
	afx_msg void OnDestroy();
	afx_msg void OnLvnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewLargeIcons();
	afx_msg void OnViewSmallIcons();
	afx_msg void OnViewList();
	afx_msg void OnViewDetails();
	afx_msg void OnUpdateViewLargeIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewSmallIcons(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDetails(CCmdUI* pCmdUI);
	afx_msg void OnFileNewDirectory();
};

#ifndef _DEBUG  // debug version in FileView.cpp
inline CWinDirDoc* CFileView::GetDocument() const
   { return reinterpret_cast<CWinDirDoc*>(m_pDocument); }
#endif

