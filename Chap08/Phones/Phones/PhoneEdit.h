#pragma once


// PhoneEdit

class PhoneEdit : public CEdit
{
	DECLARE_DYNAMIC(PhoneEdit)

public:
	PhoneEdit();
	virtual ~PhoneEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


