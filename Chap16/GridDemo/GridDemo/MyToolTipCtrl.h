#pragma once


// CMyToolTipCtrl

class CMyToolTipCtrl : public CToolTipCtrl
{

public:
	CMyToolTipCtrl();
	virtual ~CMyToolTipCtrl();

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL AddRectTool(CWnd* pWnd, LPCTSTR pszText, LPRECT pRect, UINT nIDTool);
	BOOL AddWindowTool(CWnd* pWnd, LPCTSTR pszText);
};


