#pragma once

// CalendarPropPage.h : Declaration of the CCalendarPropPage property page class.


// CCalendarPropPage : See CalendarPropPage.cpp for implementation.

class CCalendarPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCalendarPropPage)
	DECLARE_OLECREATE_EX(CCalendarPropPage)

// Constructor
public:
	CCalendarPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_CALENDAR };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

