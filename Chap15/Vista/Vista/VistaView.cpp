
// VistaView.cpp : implementation of the CVistaView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Vista.h"
#endif

#include "VistaDoc.h"
#include "VistaView.h"
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVistaView

IMPLEMENT_DYNCREATE(CVistaView, CScrollView)

BEGIN_MESSAGE_MAP(CVistaView, CScrollView)
END_MESSAGE_MAP()

// CVistaView construction/destruction

CVistaView::CVistaView() noexcept
{
}

CVistaView::~CVistaView()
{
}

BOOL CVistaView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

// CVistaView drawing

void CVistaView::OnDraw(CDC* pDC)
{
	CVistaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBitmap* pBitmap = pDoc->GetBitmap();

	if (pBitmap != NULL)
	{
		CPalette* pOldPalette{};
		CPalette* pPalette = pDoc->GetPalette();

		if (pPalette != NULL)
		{
			pOldPalette = pDC->SelectPalette(pPalette, FALSE);
			pDC->RealizePalette();
		}
		DIBSECTION ds;
		pBitmap->GetObject(sizeof(DIBSECTION), &ds);

		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap* pOldBitmap = memDC.SelectObject(pBitmap);

		pDC->BitBlt(0, 0, ds.dsBm.bmWidth, ds.dsBm.bmHeight, &memDC, 0, 0, SRCCOPY);

		memDC.SelectObject(pOldBitmap);

		if (pPalette != NULL)
		{
			pDC->SelectPalette(pOldPalette, FALSE);
		}
	}
}

void CVistaView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CString string;

	CSize sizeTotal;
	CBitmap* pBitmap = GetDocument()->GetBitmap();

	// If a bitmap is loaded, set the view size equals to the bitmap size,
	// Otherwise, set the view's width and height to 0

	if (pBitmap != NULL)
	{
		DIBSECTION ds;
		pBitmap->GetObject(sizeof(DIBSECTION), &ds);
		sizeTotal.cx = ds.dsBm.bmWidth;
		sizeTotal.cy = ds.dsBm.bmHeight;
		string.Format(_T("\t%d x %d, %d bpp"), ds.dsBm.bmWidth, ds.dsBm.bmHeight, ds.dsBmih.biBitCount);
	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 0;
		string.Empty();
	}

	AfxGetMainWnd()->SendMessage(WM_USER_UPDATE_STATS, 0, (LPARAM)(LPCTSTR)string);
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CVistaView diagnostics

#ifdef _DEBUG
void CVistaView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CVistaView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CVistaDoc* CVistaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVistaDoc)));
	return (CVistaDoc*)m_pDocument;
}
#endif //_DEBUG


// CVistaView message handlers
