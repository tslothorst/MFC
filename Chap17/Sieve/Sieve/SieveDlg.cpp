
// SieveDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Sieve.h"
#include "SieveDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSieveDlg dialog



CSieveDlg::CSieveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIEVE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSieveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSieveDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CSieveDlg::OnStart)
	ON_MESSAGE(WM_USER_THREAD_FINISHED, OnThreadFinished)
END_MESSAGE_MAP()


// CSieveDlg message handlers

BOOL CSieveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSieveDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSieveDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSieveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSieveDlg::OnStart()
{
	int nMax = GetDlgItemInt(IDC_MAX);
	if (nMax < 10)
	{
		MessageBox(_T("The number you enter must be 10 or higher"));
		GetDlgItem(IDC_MAX)->SetFocus();
		return;
	}

	SetDlgItemText(IDC_RESULT, _T(""));
	GetDlgItem(IDC_START)->EnableWindow(FALSE);

	THREADPARMS* ptp = new THREADPARMS;
	ptp->nMax = nMax;
	ptp->hWnd = m_hWnd;
	AfxBeginThread(ThreadFunc, ptp);
}

LONG CSieveDlg::OnThreadFinished(WPARAM wParam, LPARAM lParam)
{
	SetDlgItemInt(IDC_RESULT, (int)wParam);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);

	return 0;
}

// Global functions

UINT ThreadFunc(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*)pParam;
	int nMax = ptp->nMax;
	HWND hWnd = ptp->hWnd;
	delete ptp;

	int nCount = Sieve(nMax);
	::PostMessage(hWnd, WM_USER_THREAD_FINISHED, (WPARAM)nCount, 0);
	return 0;
}

int Sieve(int nMax)
{
	PBYTE pBuffer = new BYTE[nMax + 1];
	::FillMemory(pBuffer, nMax + 1, 1);

	int nLimit = 2;
	while (nLimit * nLimit < nMax)
	{
		nLimit++;
	}

	for (int i = 2; i <= nLimit; i++)
	{
		if (pBuffer[i])
		{
			for (int k = i; k <= nMax; k+=i)
			{
				pBuffer[k] = 0;
			}
		}
	}

	int nCount = 0;
	for (int i = 2; i <= nMax; i++)
	{
		if (pBuffer[i])
		{
			nCount++;
		}
	}

	delete[] pBuffer;

	return nCount;
}