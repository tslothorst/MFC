// COptionsDialog.cpp : implementation file
//

#include "pch.h"
#include "DlgDemo1.h"
#include "COptionsDialog.h"
#include "afxdialogex.h"


// COptionsDialog dialog

IMPLEMENT_DYNAMIC(COptionsDialog, CDialog)

COptionsDialog::COptionsDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_OPTIONS, pParent)
	, m_nUnits(0)
	, m_nWidth(0)
	, m_nHeight(0)
{

}

COptionsDialog::~COptionsDialog()
{
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_INCHES, m_nUnits);
	DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	DDV_MinMaxInt(pDX, m_nWidth, 1, 128);
	DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
	DDV_MinMaxInt(pDX, m_nHeight, 1, 128);
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	ON_BN_CLICKED(IDC_RESET, &COptionsDialog::OnReset)
END_MESSAGE_MAP()


// COptionsDialog message handlers


void COptionsDialog::OnReset()
{
	m_nWidth = 4;
	m_nHeight = 2;

	m_nUnits = 0;
	UpdateData(FALSE);
}
