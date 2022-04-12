
// PathListDlg.h : header file
//

#pragma once
#include "PathComboBox.h"


// CPathListDlg dialog
class CPathListDlg : public CDialogEx
{
// Construction
public:
	CPathListDlg(CWnd* pParent = nullptr);	// standard constructor
	CPathComboBox m_wndCBEx;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATHLIST_DIALOG };
#endif
	

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelEndOK();
	DECLARE_MESSAGE_MAP()
};
