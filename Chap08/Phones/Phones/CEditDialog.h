#pragma once


// CEditDialog dialog

class CEditDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditDialog)

public:
	CEditDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CEditDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_wndOK;
	CButton m_wndCancel;
	CString m_strName;
	PhoneEdit m_wndPhoneEdit;
	CString m_strPhone;
	virtual BOOL OnInitDialog();
};
