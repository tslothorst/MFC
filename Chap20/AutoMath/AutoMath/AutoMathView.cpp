
// AutoMathView.cpp : implementation of the CAutoMathView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AutoMath.h"
#endif

#include "AutoMathDoc.h"
#include "AutoMathView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoMathView

IMPLEMENT_DYNCREATE(CAutoMathView, CView)

BEGIN_MESSAGE_MAP(CAutoMathView, CView)
END_MESSAGE_MAP()

// CAutoMathView construction/destruction

CAutoMathView::CAutoMathView() noexcept
{
	// TODO: add construction code here

}

CAutoMathView::~CAutoMathView()
{
}

BOOL CAutoMathView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAutoMathView drawing

void CAutoMathView::OnDraw(CDC* /*pDC*/)
{
	CAutoMathDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CAutoMathView diagnostics

#ifdef _DEBUG
void CAutoMathView::AssertValid() const
{
	CView::AssertValid();
}

void CAutoMathView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAutoMathDoc* CAutoMathView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoMathDoc)));
	return (CAutoMathDoc*)m_pDocument;
}
#endif //_DEBUG


// CAutoMathView message handlers
