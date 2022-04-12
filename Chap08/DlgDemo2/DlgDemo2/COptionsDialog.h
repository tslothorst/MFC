#pragma once


// COptionsDialog dialog

class COptionsDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionsDialog)

public:
	COptionsDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~COptionsDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nUnits;
	int m_nWidth;
	int m_nHeight;

	// Overrides
protected:
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();

	// Implementation
protected:
	afx_msg void OnReset();

};

