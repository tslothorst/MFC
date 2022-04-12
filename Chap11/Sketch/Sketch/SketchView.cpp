
// SketchView.cpp : implementation of the CSketchView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketch.h"
#endif

#include "SketchDoc.h"
#include "SketchView.h"
#include "Line.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketchView

IMPLEMENT_DYNCREATE(CSketchView, CScrollView)

BEGIN_MESSAGE_MAP(CSketchView, CScrollView)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CSketchView construction/destruction

CSketchView::CSketchView() noexcept
{
	m_hCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);

}

CSketchView::~CSketchView()
{
}

BOOL CSketchView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

// CSketchView drawing

void CSketchView::OnDraw(CDC* pDC)
{
	CSketchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Draw the snap grid
	if (pDoc->IsGridVisible())
	{
		for (int x = 25; x < 1600; x+=25)
		{
			for (int y = -25; y > -1200; y-=25)
			{
				pDC->SetPixel(x, y, RGB(128, 128, 128));
			}
		}
	}

	// Draw the lines
	int nCount = pDoc->GetLineCount();
	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			pDoc->GetLine(i)->Draw(pDC);
		}
	}
}

void CSketchView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizes(MM_LOENGLISH, CSize(1600, 1200));
}


// CSketchView diagnostics

#ifdef _DEBUG
void CSketchView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSketchView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSketchDoc* CSketchView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketchDoc)));
	return (CSketchDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketchView message handlers


void CSketchView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (lHint == 0x7C)
	{
		CLine* pLine = (CLine*)pHint;
		ASSERT(pLine->IsKindOf(RUNTIME_CLASS(CLine)));
		CClientDC dc(this);
		OnPrepareDC(&dc);
		pLine->Draw(&dc);
		return;
	}

	CScrollView::OnUpdate(pSender, lHint, pHint);
}


BOOL CSketchView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	::SetCursor(m_hCursor);

	return TRUE;
}


void CSketchView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);

	CPoint pos = point;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&pos);

	if (GetDocument()->IsGridVisible())
	{
		pos.x = ((pos.x + 12) / 25) * 25;
		pos.y = ((pos.y - 12) / 25) * 25;
	}

	m_ptFrom = pos;
	m_ptTo = pos;
	SetCapture();
}


void CSketchView::OnMouseMove(UINT nFlags, CPoint point)
{
	CScrollView::OnMouseMove(nFlags, point);

	if (GetCapture() == this)
	{
		CPoint pos = point;
		CClientDC dc(this);
		OnPrepareDC(&dc);
		dc.DPtoLP(&pos);

		if (GetDocument()->IsGridVisible())
		{
			pos.x = ((pos.x + 12) / 25) * 25;
			pos.y = ((pos.y - 12) / 25) * 25;
		}

		if (m_ptTo != pos)
		{
			InvertLine(&dc, m_ptFrom, m_ptTo);
			InvertLine(&dc, m_ptFrom, pos);
			m_ptTo = pos;
		}
	}
}


void CSketchView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonUp(nFlags, point);

	if (GetCapture() == this)
	{
		::ReleaseCapture();

		CPoint pos = point;
		CClientDC dc(this);

		OnPrepareDC(&dc);
		dc.DPtoLP(&pos);

		if (GetDocument()->IsGridVisible())
		{
			pos.x = ((pos.x + 12) / 25) * 25;
			pos.y = ((pos.y - 12) / 25) * 25;
		}

		InvertLine(&dc, m_ptFrom, m_ptTo);

		CSketchDoc* pDoc = GetDocument();
		CLine* pLine = pDoc->AddLine(m_ptFrom, m_ptTo);
	}
}

void CSketchView::InvertLine(CDC* pDC, POINT from, POINT to)
{
	int nOldMode = pDC->SetROP2(R2_NOT);
	pDC->MoveTo(from);
	pDC->LineTo(to);
	pDC->SetROP2(nOldMode);
}
