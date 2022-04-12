#pragma once


// CSpecialStatusBar

class CSpecialStatusBar : public CStatusBar
{


public:
	CSpecialStatusBar();
	virtual ~CSpecialStatusBar();

	void SetProgress(int nPercent);
	void SetImageStats(LPCTSTR pszStats);
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CProgressCtrl m_wndProgress;
};


