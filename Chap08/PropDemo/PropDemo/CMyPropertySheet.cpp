// CMyPropertySheet.cpp : implementation file
//

#include "pch.h"
#include "PropDemo.h"
#include "CMyPropertySheet.h"
#include "stdafx.h"


// CMyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_sizePage);
	AddPage(&m_colorPage);
}

CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_sizePage);
	AddPage(&m_colorPage);
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	ON_BN_CLICKED(ID_APPLY_NOW, OnApply)
END_MESSAGE_MAP()


// CMyPropertySheet message handlers

void CMyPropertySheet::OnApply()
{
	GetActivePage()->UpdateData(TRUE);

	ELLPROP ep;
	ep.nWidth = m_sizePage.m_nWidth;
	ep.nHeight = m_sizePage.m_nHeight;
	ep.nUnits = m_sizePage.m_nUnits;
	ep.nColor = m_colorPage.m_nColor;

	GetParent()->SendMessage(WM_USER_APPLY, 0, (LPARAM)&ep);

	m_sizePage.SetModified(FALSE);
	m_colorPage.SetModified(FALSE);
}