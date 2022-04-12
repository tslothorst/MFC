#include "Hello.h"
#include <math.h>
#define SEGMENTS 500
#define PI 3.1415926

CHelloApp Hello;

BOOL CHelloApp::InitInstance() 
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}

BEGIN_MESSAGE_MAP (CMainWindow, CFrameWnd)
	ON_WM_PAINT()
	END_MESSAGE_MAP()

CMainWindow::CMainWindow() 
{
	Create(NULL, _T("The Hello Application"));
}

//void CMainWindow::OnPaint()
//{
//	CRect rect;
//	GetClientRect(&rect);
//
//	CFont font;
//	font.CreatePointFont(720, _T("Arial"));
//
//	CPaintDC dc(this);
//	dc.SelectObject(&font);
//	dc.SetBkMode(TRANSPARENT);
//
//	CString string = _T("Hello, MFC");
//
//	rect.OffsetRect(16, 16);
//	dc.SetTextColor(RGB(192, 192, 192));
//	dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//
//	rect.OffsetRect(-16, -16);
//	dc.SetTextColor(RGB(0, 0, 0));
//	dc.DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//}

void CMainWindow::OnPaint() 
{
	CRect rect;
	GetClientRect(&rect);

	CPaintDC dc(this);
	dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	dc.SetBkMode(TRANSPARENT);

	for (int i = 0; i < 3600; i+=150)
	{
		LOGFONT lf;
		::ZeroMemory(&lf, sizeof(lf));
		lf.lfHeight = 160;
		lf.lfWeight = FW_BOLD;
		lf.lfEscapement = i;

		lf.lfOrientation = i;
		::lstrcpy(lf.lfFaceName, _T("Arial"));

		CFont font;
		font.CreatePointFontIndirect(&lf);

		CFont* pOldFont = dc.SelectObject(&font);
		dc.TextOut(0, 0, CString(_T("            Hello, MFC")));
		dc.SelectObject(pOldFont);
	}
}