#pragma once

// CalendarCtrl.h : Declaration of the CCalendarCtrl ActiveX Control class.


// CCalendarCtrl : See CalendarCtrl.cpp for implementation.

class CCalendarCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCalendarCtrl)

// Constructor
public:
	CCalendarCtrl();

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	BOOL LeapYear(int nYear);
	static const int m_nDaysPerMonth[];
	int m_nDay;
	int m_nMonth;
	int m_nYear;
	~CCalendarCtrl();

	DECLARE_OLECREATE_EX(CCalendarCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CCalendarCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCalendarCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CCalendarCtrl)		// Type name and misc status

// Message maps
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	BOOL m_bRedSundays;
	afx_msg void OnRedSundaysChanged();
	afx_msg DATE GetDate();
	afx_msg BOOL SetDate(short nYear, short nMonth, short nDay);
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	void FireNewDay(short nDay)
	{
		FireEvent(eventidNewDay, EVENT_PARAM(VTS_I2), nDay);
	}
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
		dispidRedSundays = 1L,
		dispidGetDate = 2L,
		dispidSetDate = 3L,
		eventidNewDay = 1L
	};
};

