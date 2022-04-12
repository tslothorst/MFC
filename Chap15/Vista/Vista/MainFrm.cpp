
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "Vista.h"
#include "stdafx.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_MESSAGE(WM_USER_UPDATE_STATS, OnUpdateImageStats)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// Size the status bar's rightmost pane to hold a text string

	TEXTMETRIC tm;
	CClientDC dc(this);
	CFont* pFont = m_wndStatusBar.GetFont();
	CFont* pOldFont = dc.SelectObject(pFont);
	dc.GetTextMetrics(&tm);
	dc.SelectObject(pOldFont);

	int cxWidth;
	UINT nID;
	UINT nStyle;
	m_wndStatusBar.GetPaneInfo(1, nID, nStyle, cxWidth);
	cxWidth = tm.tmAveCharWidth * 24;
	m_wndStatusBar.SetPaneInfo(1, nID, nStyle, cxWidth);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



BOOL CMainFrame::OnQueryNewPalette()
{
	CDocument* pDoc = GetActiveDocument();
	if (pDoc != NULL)
	{
		GetActiveDocument()->UpdateAllViews(NULL);
	}

	return TRUE;
}


void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	if (pFocusWnd != this)
	{
		CDocument* pDoc = GetActiveDocument();
		if (pDoc != NULL)
		{
			GetActiveDocument()->UpdateAllViews(NULL);
		}
	}
}

LRESULT CMainFrame::OnUpdateImageStats(WPARAM wParam, LPARAM lParam)
{
	m_wndStatusBar.SetPaneText(1, (LPCTSTR)lParam, TRUE);
	return 0;
}