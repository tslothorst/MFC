
// SieveDlg.h : header file
//

#pragma once

#define WM_USER_THREAD_FINISHED WM_USER+0x100

UINT ThreadFunc(LPVOID pParam);
int Sieve(int nMax);

typedef struct tagTHREADPARMS {
	int nMax;
	HWND hWnd;
} THREADPARMS;

// CSieveDlg dialog
class CSieveDlg : public CDialogEx
{
// Construction
public:
	CSieveDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIEVE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnStart();
	afx_msg LONG OnThreadFinished(WPARAM wParam, LPARAM lParam);
};
