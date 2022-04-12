
// HtmlClockView.cpp : implementation of the CHtmlClockView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HtmlClock.h"
#endif

#include "HtmlClockDoc.h"
#include "HtmlClockView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHtmlClockView

IMPLEMENT_DYNCREATE(CHtmlClockView, CHtmlView)

BEGIN_MESSAGE_MAP(CHtmlClockView, CHtmlView)
END_MESSAGE_MAP()

// CHtmlClockView construction/destruction

CHtmlClockView::CHtmlClockView() noexcept
{
	// TODO: add construction code here

}

CHtmlClockView::~CHtmlClockView()
{
}

BOOL CHtmlClockView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

void CHtmlClockView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	TCHAR szPath[MAX_PATH];
	::GetModuleFileName(NULL, szPath, sizeof(szPath) / sizeof(TCHAR));

	CString string = szPath;
	int nIndex = string.ReverseFind(_T('\\'));
	ASSERT(nIndex != -1);
	string = string.Left(nIndex + 1) + _T("Clock.htm");
	Navigate(string);
}


// CHtmlClockView diagnostics

#ifdef _DEBUG
void CHtmlClockView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHtmlClockView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHtmlClockDoc* CHtmlClockView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHtmlClockDoc)));
	return (CHtmlClockDoc*)m_pDocument;
}
#endif //_DEBUG


// CHtmlClockView message handlers


void CHtmlClockView::OnDraw(CDC* pDC)
{
	CHtmlClockDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


void CHtmlClockView::OnTitleChange(LPCTSTR lpszText)
{
	CHtmlView::OnTitleChange(lpszText);
	AfxGetMainWnd()->SetWindowText(lpszText);
}
