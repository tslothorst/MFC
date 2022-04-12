
// DriveTreeView.h : interface of the CDriveTreeView class
//

#pragma once


class CDriveTreeView : public CTreeView
{
protected: // create from serialization only
	CDriveTreeView() noexcept;
	DECLARE_DYNCREATE(CDriveTreeView)

// Attributes
public:
	CDriveTreeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CDriveTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL AddDriveItem(LPCTSTR pszDrive);
	int AddDirectories(HTREEITEM hItem, LPCTSTR pszPath);
	void DeleteAllChildren(HTREEITEM hItem);
	void DeleteFirstChild(HTREEITEM hItem);
	CString GetPathFromItem(HTREEITEM hItem);
	BOOL SetButtonState(HTREEITEM hItem, LPCTSTR pszPath);
	int AddDrives();
	CImageList m_ilDrives;
	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* pDC);
public:
	afx_msg void OnTvnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG  // debug version in DriveTreeView.cpp
inline CDriveTreeDoc* CDriveTreeView::GetDocument() const
   { return reinterpret_cast<CDriveTreeDoc*>(m_pDocument); }
#endif

