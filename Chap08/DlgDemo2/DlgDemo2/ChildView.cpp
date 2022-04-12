
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "DlgDemo2.h"
#include "ChildView.h"
#include "COptionsDialog.h"
#include "CustomMessages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	int m_nWidth = 4;
	int m_nHeight = 2;
	int m_nUnits = 0;
	m_pDlg = NULL;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPTIONS, &CChildView::OnFileOptions)
	ON_MESSAGE(WM_USER_APPLY, OnApply)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush brush(RGB(255, 0, 255));
	CBrush* pOldBrush = dc.SelectObject(&brush);

	switch (m_nUnits)
	{
	case 0: // Inches
		dc.SetMapMode(MM_LOENGLISH);
		dc.Rectangle(0, 0, m_nWidth * 100, -m_nHeight * 100);
		break;
	case 1: // Centimeters
		dc.SetMapMode(MM_LOMETRIC);
		dc.Rectangle(0, 0, m_nWidth * 100, -m_nHeight * 100);
		break;
	case 2:
		dc.SetMapMode(MM_TEXT);
		dc.Rectangle(0, 0, m_nWidth, m_nHeight);
		break;
	}
	dc.SelectObject(pOldBrush);
}



void CChildView::OnFileOptions()
{
	// If the dialog box already exists, display it

	if (m_pDlg != NULL)
	{
		m_pDlg->SetFocus();
	}

	// If the dialog box doesn't already exists, create it

	else
	{
		m_pDlg = new COptionsDialog;
		m_pDlg->m_nWidth = m_nWidth;
		m_pDlg->m_nHeight = m_nHeight;
		m_pDlg->m_nUnits = m_nUnits;
		m_pDlg->Create(IDD_OPTIONS);
		m_pDlg->ShowWindow(SW_SHOW);
	}
}

LRESULT CChildView::OnApply(WPARAM wParam, LPARAM lParam)
{
	RECTPROP* prp = (RECTPROP*)lParam;
	m_nWidth = prp->nWidth;
	m_nHeight = prp->nHeight;
	m_nUnits = prp->nUnits;
	Invalidate();
	return 0;
}

LRESULT CChildView::OnDialogDestroyed(WPARAM wParam, LPARAM lParam)
{
	m_pDlg = NULL;
	return 0;
}
