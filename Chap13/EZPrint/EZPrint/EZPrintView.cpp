
// EZPrintView.cpp : implementation of the CEZPrintView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "EZPrint.h"
#endif

#include "EZPrintDoc.h"
#include "EZPrintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEZPrintView

IMPLEMENT_DYNCREATE(CEZPrintView, CView)

BEGIN_MESSAGE_MAP(CEZPrintView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEZPrintView construction/destruction

CEZPrintView::CEZPrintView() noexcept
{
}

CEZPrintView::~CEZPrintView()
{
}

BOOL CEZPrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CEZPrintView drawing

void CEZPrintView::OnDraw(CDC* pDC)
{
	CPen pen(PS_SOLID, 50, RGB(0, 0, 255));
	CBrush brush(RGB(255, 255, 0));

	pDC->SetMapMode(MM_LOMETRIC);
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	pDC->Ellipse(100, -100, 1100, -1100);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}


// CEZPrintView printing

BOOL CEZPrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CEZPrintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEZPrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEZPrintView diagnostics

#ifdef _DEBUG
void CEZPrintView::AssertValid() const
{
	CView::AssertValid();
}

void CEZPrintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEZPrintDoc* CEZPrintView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEZPrintDoc)));
	return (CEZPrintDoc*)m_pDocument;
}
#endif //_DEBUG


// CEZPrintView message handlers
