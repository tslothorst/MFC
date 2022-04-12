#include "Accel.h"

CAccelApp accel;

BOOL CAccelApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL, _T("Accel"), WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL);
}

int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	CClientDC dc(this);
	m_nCellWidth = dc.GetDeviceCaps(LOGPIXELSX);
	m_nCellHeight = dc.GetDeviceCaps(LOGPIXELSY) / 4;
	m_nRibbonWidth = m_nCellWidth / 2;
	m_nViewWidth = (26 * m_nCellWidth) + m_nRibbonWidth;
	m_nViewHeight = m_nCellHeight * 100;
	return 0;
}

void CMainWindow::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// Set horizontal scrolling params
	int nHScrollMax = 0;
	m_nHScrollPos = m_nHPageSize = 0;

	if (cx < m_nViewWidth)
	{
		nHScrollMax = m_nViewWidth - 1;
		m_nHPageSize = cx;
		m_nHScrollPos = min(m_nHScrollPos, m_nViewHeight - m_nHPageSize - 1);
	}

	SCROLLINFO si;
	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nHScrollMax;
	si.nPos = m_nHScrollPos;
	si.nPage = m_nHPageSize;

	SetScrollInfo(SB_HORZ, &si, TRUE);

	// Set vertical scrolling params
	int nVScrollMax = 0;
	m_nVScrollPos = m_nVPageSize = 0;

	if (cy < m_nViewHeight)
	{
		nVScrollMax = m_nViewHeight - 1;
		m_nVPageSize = cy;
		m_nVScrollPos = min(m_nVScrollPos, m_nViewHeight - m_nVPageSize - 1);
	}

	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nVScrollMax;
	si.nPos = m_nVScrollPos;
	si.nPage = m_nVPageSize;

	SetScrollInfo(SB_VERT, &si, TRUE);
}

void CMainWindow::OnPaint() 
{
	CPaintDC dc(this);

	// Set Windows origin to reflect current scroll position

	dc.SetWindowOrg(m_nHScrollPos, m_nVScrollPos);

	// Draw grid lines

	CPen pen(PS_SOLID, 0, RGB(192, 192, 192));
	CPen* pOldPen = dc.SelectObject(&pen);

	for (int i = 0; i < 99; i++)
	{
		int y = (i * m_nCellHeight) + m_nCellHeight;
		dc.MoveTo(0, y);
		dc.LineTo(m_nViewWidth, y);
	}

	for (int j = 0; j < 26; j++)
	{
		int x = (j * m_nCellWidth) + m_nRibbonWidth;
		dc.MoveTo(x, 0);
		dc.LineTo(x, m_nViewHeight);
	}

	dc.SelectObject(pOldPen);

	// Draw the bodies of the rows and columns headers

	CBrush brush;
	brush.CreateStockObject(LTGRAY_BRUSH);

	CRect rcTop(0, 0, m_nViewWidth, m_nCellHeight);
	dc.FillRect(rcTop, &brush);
	CRect rcLeft(0, 0, m_nRibbonWidth, m_nViewHeight);
	dc.FillRect(rcLeft, &brush);

	dc.MoveTo(0, m_nCellHeight);
	dc.LineTo(m_nViewWidth, m_nCellHeight);
	dc.MoveTo(m_nRibbonWidth, 0);
	dc.LineTo(m_nRibbonWidth, m_nViewHeight);

	dc.SetBkMode(TRANSPARENT);

	// Add numbers and button outlines to the row headers

	for (int i = 0; i < 99; i++)
	{
		int y = (i * m_nCellHeight) + m_nCellHeight;
		dc.MoveTo(0, y);
		dc.LineTo(m_nRibbonWidth, y);

		CString string;
		string.Format(_T("%d"), i, +1);

		CRect rect(0, y, m_nRibbonWidth, y + m_nCellHeight);
		dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		rect.top++;
		dc.Draw3dRect(rect, RGB(255, 255, 255), RGB(128, 128, 128));
	}

	// Add letters and button outlines to the column headers

	for (int j = 0; j < 26; j++)
	{
		int x = (j * m_nCellWidth) + m_nRibbonWidth;
		dc.MoveTo(x, 0);
		dc.LineTo(x, m_nCellHeight);

		CString string;
		string.Format(_T("%c"), j + 'A');

		CRect rect(x, 0, x + m_nCellWidth, m_nCellHeight);
		dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		rect.left++;
		dc.Draw3dRect(rect, RGB(255, 255, 255), RGB(128, 128, 128));
	}
}

void CMainWindow::OnHScroll(UINT nCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;

	switch (nCode)
	{
	case SB_LINELEFT:
		nDelta = -linesize;
		break;
	case SB_PAGELEFT:
		nDelta = -m_nHPageSize;
		break;
	case SB_THUMBTRACK:
		nDelta = (int)nPos - m_nHScrollPos;
		break;
	case SB_PAGERIGHT:
		nDelta = m_nHPageSize;
		break;
	case SB_LINERIGHT:
		nDelta = linesize;
		break;
	default:		// Ignore all other scrollbar messages
		return;
	}

	int nScrollPos = m_nHScrollPos + nDelta;
	int nMaxPos = m_nViewWidth - m_nHPageSize;

	if (nScrollPos <0)
	{
		nDelta = -m_nHPageSize;
	}
	else if (nScrollPos > nMaxPos)
	{
		nDelta = nMaxPos - m_nHScrollPos;
	}

	if (nDelta != 0)
	{
		m_nHScrollPos += nDelta;
		SetScrollPos(SB_HORZ, m_nHScrollPos, TRUE);
		ScrollWindow(-nDelta, 0);
	}
}

void CMainWindow::OnVScroll(UINT nCode, UINT nPos, CScrollBar* pScrollbar)
{
	int nDelta;

	switch (nCode)
	{
	case SB_LINEUP:
		nDelta = -linesize;
		break;
	case SB_PAGEUP:
		nDelta = -m_nVPageSize;
		break;
	case SB_THUMBTRACK:
		nDelta = (int)nPos - m_nVScrollPos;
		break;
	case SB_PAGEDOWN:
		nDelta = m_nVPageSize;
		break;
	case SB_LINEDOWN:
		nDelta = linesize;
		break;
	default:		// Ignore all other scrollbar messages
		return;
	}

	int nScrollPos = m_nVScrollPos + nDelta;
	int nMaxPos = m_nViewHeight - m_nVPageSize;

	if (nScrollPos < 0)
	{
		nDelta = -m_nVScrollPos;
	}
	else if (nScrollPos > nMaxPos)
	{
		nDelta = nMaxPos - m_nVScrollPos;
	}

	if (nDelta != 0)
	{
		m_nVScrollPos += nDelta;
		SetScrollPos(SB_VERT, m_nVScrollPos, TRUE);
		ScrollWindow(0, -nDelta);
	}
}