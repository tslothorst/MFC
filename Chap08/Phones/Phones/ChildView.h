
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "CPhoneListBox.h"

// CChildView window

class CChildView : public CPhoneListBox
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();
	
	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	BOOL SaveFile(LPCTSTR pszFile);
	BOOL LoadFile(LPCTSTR pszFile);
	
	CString m_strPathName;
	//static const TCHAR m_szFilters[];
	afx_msg void OnNewEntry();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
};

