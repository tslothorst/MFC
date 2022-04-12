// PhoneEdit.cpp : implementation file
//

#include "pch.h"
#include "Phones.h"
#include "PhoneEdit.h"


// PhoneEdit

IMPLEMENT_DYNAMIC(PhoneEdit, CEdit)

PhoneEdit::PhoneEdit()
{

}

PhoneEdit::~PhoneEdit()
{
}


BEGIN_MESSAGE_MAP(PhoneEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// PhoneEdit message handlers




void PhoneEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (((nChar >= _T('0')) && (nChar <= _T('9'))) ||
		(nChar == VK_BACK) || (nChar == _T('(')) || (nChar == _T(')')) ||
		(nChar == _T('-')) || (nChar == _T(' ')))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}	
}
