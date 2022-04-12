#pragma once


// CPhoneListBox

class CPhoneListBox : public CListBox
{
	DECLARE_DYNAMIC(CPhoneListBox)

public:
	CPhoneListBox();
	virtual ~CPhoneListBox();
	void NewEntry();

protected:
	CFont m_font;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditItem();
	DECLARE_MESSAGE_MAP()
};


