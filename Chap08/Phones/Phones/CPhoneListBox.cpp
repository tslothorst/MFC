// CPhoneListBox.cpp : implementation file
//

#include "pch.h"
#include "Phones.h"
#include "CPhoneListBox.h"
#include "PhoneEdit.h"
#include "CEditDialog.h"

// CPhoneListBox

IMPLEMENT_DYNAMIC(CPhoneListBox, CListBox)

CPhoneListBox::CPhoneListBox()
{

}

CPhoneListBox::~CPhoneListBox()
{
}


BEGIN_MESSAGE_MAP(CPhoneListBox, CListBox)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(LBN_DBLCLK, OnEditItem)
END_MESSAGE_MAP()



// CPhoneListBox message handlers

int CPhoneListBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	m_font.CreatePointFont(80, _T("MS Sans Serif"));
	SetFont(&m_font, FALSE);
	SetTabStops(128);
	return 0;
}

void CPhoneListBox::OnEditItem()
{
	CEditDialog dlg;

	CString strItem;
	int nIndex = GetCurSel();
	GetText(nIndex, strItem);
	int nPos = strItem.Find(_T('\t'));

	dlg.m_strName = strItem.Left(nPos);
	dlg.m_strPhone = strItem.Right(strItem.GetLength() - nPos - 1);

	if (dlg.DoModal() == IDOK)
	{
		strItem = dlg.m_strName + _T('\t') + dlg.m_strPhone;
		DeleteString(nIndex);
		AddString(strItem);
	}
	SetFocus();
}

void CPhoneListBox::NewEntry()
{
	CEditDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		CString strItem = dlg.m_strName + _T('\t') + dlg.m_strPhone;
		AddString(strItem);
	}
	SetFocus();
}
