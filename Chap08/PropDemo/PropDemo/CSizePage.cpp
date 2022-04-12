// CSizePage.cpp : implementation file
//

#include "pch.h"
#include "PropDemo.h"
#include "CSizePage.h"
#include "afxdialogex.h"


// CSizePage dialog

IMPLEMENT_DYNAMIC(CSizePage, CPropertyPage)

CSizePage::CSizePage()
	: CPropertyPage(IDD_CSizePage)
	, m_nWidth(0)
	, m_nUnits(0)
	, m_nHeight(0)
{

}

CSizePage::~CSizePage()
{
}

void CSizePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDV_MinMaxInt(pDX, m_nWidth, 1, 128);
	DDX_Radio(pDX, IDC_INCHES, m_nUnits);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDV_MinMaxInt(pDX, m_nHeight, 1, 128);
}


BEGIN_MESSAGE_MAP(CSizePage, CPropertyPage)
	ON_EN_CHANGE(IDC_WIDTH, &CSizePage::OnChange)
	ON_EN_CHANGE(IDC_HEIGHT, &CSizePage::OnChange)
	ON_BN_CLICKED(IDC_INCHES, &CSizePage::OnChange)
	ON_BN_CLICKED(IDC_CENTIMETERS, &CSizePage::OnChange)
	ON_BN_CLICKED(IDC_PIXELS, &CSizePage::OnChange)
END_MESSAGE_MAP()


// CSizePage message handlers


void CSizePage::OnChange()
{
	SetModified(TRUE);
}
