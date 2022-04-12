
// WandererView.cpp : implementation of the CWandererView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Wanderer.h"
#endif

#include "WandererDoc.h"
#include "WandererView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWandererView

IMPLEMENT_DYNCREATE(CWandererView, CView)

BEGIN_MESSAGE_MAP(CWandererView, CView)
END_MESSAGE_MAP()

// CWandererView construction/destruction

CWandererView::CWandererView() noexcept
{
	// TODO: add construction code here

}

CWandererView::~CWandererView()
{
}

BOOL CWandererView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CWandererView drawing

void CWandererView::OnDraw(CDC* /*pDC*/)
{
	CWandererDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CWandererView diagnostics

#ifdef _DEBUG
void CWandererView::AssertValid() const
{
	CView::AssertValid();
}

void CWandererView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWandererDoc* CWandererView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWandererDoc)));
	return (CWandererDoc*)m_pDocument;
}
#endif //_DEBUG


// CWandererView message handlers
