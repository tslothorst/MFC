
#pragma once
#include <afxwin.h>

class CFontView : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CWnd
{
protected:

	static constexpr int IDC_PRINT = 100;
	static constexpr int IDC_CHECKBOX = 101;
	static constexpr int IDC_LISTBOX = 102;
	static constexpr int IDC_SAMPLE = 103;

	int m_cxChar;
	int m_cyChar;

	CFont m_fontMain;
	CFont m_fontSample;

	CStatic m_wndLBTitle;
	CListBox m_wndListBox;
	CButton m_wndCheckBox;
	CButton m_wndGroupBox;
	CStatic m_wndSampleText;
	CButton m_wndPushButton;

	void FillListBox();

public:
	CMainWindow();

	static int CALLBACK EnumFontFamProc(ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, int nFontType, LPARAM lParam);

protected:
	virtual void PostNcDestroy();

	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnPushButtonClicked();
	afx_msg void OnCheckBoxClicked();
	afx_msg void OnSelChange();

	DECLARE_MESSAGE_MAP()
};