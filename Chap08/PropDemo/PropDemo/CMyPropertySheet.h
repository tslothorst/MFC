#pragma once
#include "CSizePage.h"
#include "CColorPage.h"



// CMyPropertySheet

class CMyPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropertySheet)

public:
	CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~CMyPropertySheet();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnApply();
public:
	CSizePage m_sizePage;
	CColorPage m_colorPage;
};


