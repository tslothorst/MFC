#pragma once
#include "MyToolTipCtrl.h"

// CSettingsDialog dialog

class CSettingsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingsDialog)

public:
	CSettingsDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSettingsDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_SETTINGDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSpinButtonCtrl m_wndSpinHorz;
	CSpinButtonCtrl m_wndSpinVert;
	int m_cy;
	int m_cx;
	CSliderCtrl m_wndSlider;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CMyToolTipCtrl m_ctlTT;
	int m_nWeight;
};
