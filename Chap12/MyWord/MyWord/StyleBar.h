#pragma once


// CStyleBar

class CStyleBar : public CToolBar
{

public:
	static int CALLBACK EnumFontNameProc(ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, int nFontType, LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()
	void InitTypefaceList(CDC* pDC);
	CFont m_font;
	CComboBox m_wndFontNames;
	CComboBox m_wndFontSizes;
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelectFont();
	afx_msg void OnSelectSize();
	afx_msg void OnCloseUp();
};


