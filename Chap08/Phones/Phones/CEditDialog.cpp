// CEditDialog.cpp : implementation file
//

#include "pch.h"
#include "Phones.h"
#include "PhoneEdit.h"
#include "CEditDialog.h"
#include "afxdialogex.h"


// CEditDialog dialog

IMPLEMENT_DYNAMIC(CEditDialog, CDialog)

CEditDialog::CEditDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EDITDLG, pParent)
	, m_strName(_T(""))
	, m_strPhone(_T(""))
{

}

CEditDialog::~CEditDialog()
{
}

void CEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_wndOK);
	DDX_Control(pDX, IDCANCEL, m_wndCancel);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 32);
	DDX_Control(pDX, IDC_PHONE, m_wndPhoneEdit);
	DDX_Text(pDX, IDC_PHONE, m_strPhone);
}


BEGIN_MESSAGE_MAP(CEditDialog, CDialog)
END_MESSAGE_MAP()


// CEditDialog message handlers


BOOL CEditDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndOK.SetIcon(AfxGetApp()->LoadIcon(IDI_OK));
	m_wndCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_CANCEL));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
