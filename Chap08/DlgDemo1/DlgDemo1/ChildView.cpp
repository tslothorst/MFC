
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "DlgDemo1.h"
#include "ChildView.h"
#include "COptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_nWidth = 4;
	m_nHeight = 2;
	m_nUnits = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPTIONS, &CChildView::OnFileOptions)
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
		dc.Rectangle(0, 0, m_nWidth * 100, -m_nHeight * 100);
		break;
	}
	dc.SelectObject(pOldBrush);
}



void CChildView::OnFileOptions()
{
	COptionsDialog dlg;

	dlg.m_nWidth = m_nWidth;
	dlg.m_nHeight = m_nHeight;
	dlg.m_nUnits = m_nUnits;

	if (dlg.DoModal() == IDOK)
	{
		m_nWidth = dlg.m_nWidth;
		m_nHeight = dlg.m_nHeight;
		m_nUnits = dlg.m_nUnits;
		Invalidate();
	}
}
