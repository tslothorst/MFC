#pragma once


// CSizePage dialog

class CSizePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSizePage)

public:
	CSizePage();
	virtual ~CSizePage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSizePage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_nWidth;
	int m_nUnits;
	int m_nHeight;
	afx_msg void OnChange();
};
