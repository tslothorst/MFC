
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "MyWord.h"


#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Tell the frame window to permit docking
	EnableDocking(CBRS_ALIGN_ANY);

	// Create the toolbar, stylebar and status bar
	if (!CreateToolBar() ||
		!CreateStyleBar() ||
		!CreateStatusBar())
	{
		return -1;
	}

	// Load the saved bar state (if any)
	LoadBarState(_T("MainBarState"));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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

BOOL CMainFrame::CreateToolBar()
{
	if (!m_wndToolBar.Create(this) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		return FALSE;
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.SetWindowText(_T("Main"));
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return TRUE;
}

BOOL CMainFrame::CreateStyleBar()
{
	if (!m_wndStyleBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, IDR_STYLE_BAR))
	{
		return FALSE;
	}

	m_wndStyleBar.SetWindowText(_T("Styles"));
	m_wndStyleBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
	DockControlBar(&m_wndStyleBar);

	return TRUE;
}

BOOL CMainFrame::CreateStatusBar()
{
	static UINT nIndicators[] = {
		ID_SEPARATOR,
		ID_INDICATOR_LINE,
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM
	};

	if (!m_wndStatusBar.Create(this))
	{
		return FALSE;
	}

	m_wndStatusBar.SetIndicators(nIndicators, 4);

	return TRUE;
}

void CMainFrame::OnClose()
{
	SaveBarState(_T("MainBarState"));
	CFrameWnd::OnClose();
}
