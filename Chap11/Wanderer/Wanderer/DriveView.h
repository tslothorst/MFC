#pragma once


// CDriveView view

class CDriveView : public CTreeView
{
	DECLARE_DYNCREATE(CDriveView)

protected:
	CDriveView() noexcept;

// Attributes
public:
	CWandererDoc* GetDocument() const;

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CDriveView();
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
	afx_msg void OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult);
};

#ifndef _DEBUG  // debug version in DriveTreeView.cpp
inline CWandererDoc* CDriveView::GetDocument() const
{
	return reinterpret_cast<CWandererDoc*>(m_pDocument);
}
#endif

