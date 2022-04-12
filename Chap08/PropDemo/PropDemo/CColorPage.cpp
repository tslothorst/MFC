// CColorPage.cpp : implementation file
//

#include "pch.h"
#include "PropDemo.h"
#include "CColorPage.h"
#include "afxdialogex.h"


// CColorPage dialog

IMPLEMENT_DYNAMIC(CColorPage, CPropertyPage)

CColorPage::CColorPage()
	: CPropertyPage(IDD_CColorPage)
	, m_nColor(0)
{

}

CColorPage::~CColorPage()
{
}

void CColorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RED, m_nColor);
}


BEGIN_MESSAGE_MAP(CColorPage, CPropertyPage)
	ON_BN_CLICKED(IDC_RED, &CColorPage::OnChange)
	ON_BN_CLICKED(IDC_GREEN, &CColorPage::OnChange)
	ON_BN_CLICKED(IDC_BLUE, &CColorPage::OnChange)
END_MESSAGE_MAP()

const COLORREF CColorPage::m_clrColors[3] =
{
	RGB(255,0,0),	// Red
	RGB(0,255,0),	// Green
	RGB(0,0,255)	// Blue
};

// CColorPage message handlers

void CColorPage::OnChange()
{
	SetModified(TRUE);
}
