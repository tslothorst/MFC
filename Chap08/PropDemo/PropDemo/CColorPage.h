#pragma once


// CColorPage dialog

class CColorPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CColorPage)

public:
	CColorPage();
	virtual ~CColorPage();
	static const COLORREF m_clrColors[3];

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CColorPage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnChange();
public:
	int m_nColor;
};
