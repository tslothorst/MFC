
// DlgCalcDlg.h : header file
//

#pragma once


// CDlgCalcDlg dialog
class CDlgCalcDlg : public CDialogEx
{
// Construction
public:
	void UpdateDisplay(LPCTSTR pzDisplay);
	CDlgCalcDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGCALC_DIALOG };
#endif
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);


// Implementation
protected:

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnAdd();
	afx_msg void OnSubstract();
	afx_msg void OnMultiply();
	afx_msg void OnDivide();
	afx_msg void OnEnter();
	afx_msg void OnChangeSign();
	afx_msg void OnExponent();
	afx_msg void OnStore();
	afx_msg void OnRecall();
	afx_msg void OnFix();
	afx_msg void OnClear();
	afx_msg void OnDecimal();
	afx_msg void OnDelete();
	afx_msg void OnDigit(UINT nID);
protected:
	void DropStack();
	void LiftStack();
	void DisplayXRegister();

	double m_dblStack[4];
	double m_dblMemory;
	CString m_strDisplay;
	CString m_strFormat;
	CRect m_rect;
	int m_cxChar;
	int m_cyChar;

	BOOL m_bFixPending;
	BOOL m_bErrorFlag;
	BOOL m_bDecimalInString;
	BOOL m_bStackLiftEnabled;
	BOOL m_bNewX;

	HICON m_hIcon;
	HACCEL m_hAccel;
};
