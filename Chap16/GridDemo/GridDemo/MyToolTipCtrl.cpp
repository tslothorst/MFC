// MyToolTipCtrl.cpp : implementation file
//

#include "pch.h"
#include "GridDemo.h"
#include "MyToolTipCtrl.h"


// CMyToolTipCtrl

CMyToolTipCtrl::CMyToolTipCtrl()
{

}

CMyToolTipCtrl::~CMyToolTipCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyToolTipCtrl, CToolTipCtrl)
END_MESSAGE_MAP()



// CMyToolTipCtrl message handlers

BOOL CMyToolTipCtrl::AddWindowTool(CWnd* pWnd, LPCTSTR pszText)
{
	TOOLINFO ti;
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	ti.hwnd = pWnd->GetParent()->GetSafeHwnd();
	ti.uId = (UINT)pWnd->GetSafeHwnd();
	ti.hinst = AfxGetInstanceHandle();
	ti.lpszText = (LPTSTR)pszText;

	return (BOOL)SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti);
}

BOOL CMyToolTipCtrl::AddRectTool(CWnd* pWnd, LPCTSTR pszText, LPRECT pRect, UINT nIDTool)
{
	TOOLINFO ti;
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_SUBCLASS;
	ti.hwnd = pWnd->GetSafeHwnd();
	ti.uId = nIDTool;
	ti.hinst = AfxGetInstanceHandle();
	ti.lpszText = (LPTSTR)pszText;
	::CopyRect(&ti.rect, pRect);

	return (BOOL)SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti);
}
