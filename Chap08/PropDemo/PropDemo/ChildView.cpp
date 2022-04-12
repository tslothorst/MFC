
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "PropDemo.h"
#include "ChildView.h"
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CColorPage.h"
#include "CMyPropertySheet.h"


// CChildView

CChildView::CChildView()
{
	m_nWidth = 4;
	m_nHeight = 2;
	m_nUnits = 0;
	m_nColor = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_PROPERTIES, &CChildView::OnFileProperties)
	ON_MESSAGE(WM_USER_APPLY, &CChildView::OnApply)
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
	
	CBrush brush(CColorPage::m_clrColors[m_nColor]);
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



void CChildView::OnFileProperties()
{
	CMyPropertySheet ps(_T("Properties"));
	ps.m_sizePage.m_nWidth = m_nWidth;
	ps.m_sizePage.m_nHeight = m_nHeight;
	ps.m_sizePage.m_nUnits = m_nUnits;
	ps.m_colorPage.m_nColor = m_nColor;

	if (ps.DoModal() == IDOK)
	{
		m_nWidth = ps.m_sizePage.m_nWidth;
		m_nHeight = ps.m_sizePage.m_nHeight;
		m_nUnits = ps.m_sizePage.m_nUnits;
		m_nColor = ps.m_colorPage.m_nColor;
		Invalidate();
	}
}

LRESULT CChildView::OnApply(WPARAM wParam, LPARAM lParam)
{
	ELLPROP* pep = (ELLPROP*)lParam;
	m_nWidth = pep->nWidth;
	m_nHeight = pep->nHeight;
	m_nUnits = pep->nUnits;
	m_nColor = pep->nColor;
	Invalidate();
	return 0;
}
