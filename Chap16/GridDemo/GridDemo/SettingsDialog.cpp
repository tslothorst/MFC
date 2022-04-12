// SettingsDialog.cpp : implementation file
//

#include "pch.h"
#include "GridDemo.h"
#include "SettingsDialog.h"
#include "afxdialogex.h"



// CSettingsDialog dialog

IMPLEMENT_DYNAMIC(CSettingsDialog, CDialogEx)

CSettingsDialog::CSettingsDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_SETTINGDLG, pParent)
	, m_cx(0)
	, m_cy(0)
{

}

CSettingsDialog::~CSettingsDialog()
{
}

void CSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPINHORZ, m_wndSpinHorz);
	DDX_Control(pDX, IDC_SPINVERT, m_wndSpinVert);
	DDX_Text(pDX, IDC_EDITVERT, m_cy);
	DDX_Text(pDX, IDC_EDITHORZ, m_cx);
	DDX_Control(pDX, IDC_SLIDER, m_wndSlider);
}


BEGIN_MESSAGE_MAP(CSettingsDialog, CDialogEx)
END_MESSAGE_MAP()


// CSettingsDialog message handlers


BOOL CSettingsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Initialize the slider control
	m_wndSlider.SetRange(0, 8);
	m_wndSlider.SetPos(m_nWeight);

	// Initialize the spin button controls
	m_wndSpinHorz.SetRange(2, 64);
	m_wndSpinVert.SetRange(2, 64);

	// Create and initialize a tooltip control
	m_ctlTT.Create(this);
	m_ctlTT.AddWindowTool(GetDlgItem(IDC_SLIDER), MAKEINTRESOURCE(IDS_SLIDER));
	m_ctlTT.AddWindowTool(GetDlgItem(IDC_EDITHORZ), MAKEINTRESOURCE(IDS_EDITHORZ));
	m_ctlTT.AddWindowTool(GetDlgItem(IDC_EDITVERT), MAKEINTRESOURCE(IDS_EDITVERT));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CSettingsDialog::OnOK()
{
	// Read the slider control's thumb position
	// before dismissing the dialog.

	m_nWeight = m_wndSlider.GetPos();
	CDialogEx::OnOK();
}
