// CalendarPropPage.cpp : Implementation of the CCalendarPropPage property page class.

#include "pch.h"
#include "framework.h"
#include "Calendar.h"
#include "CalendarPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCalendarPropPage, COlePropertyPage)

// Message map

BEGIN_MESSAGE_MAP(CCalendarPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCalendarPropPage, "MFCACTIVEXCONT.CalendarPropPage.1",
	0xe570ea96,0xb167,0x44d2,0x87,0xa6,0x65,0x4e,0x6b,0xef,0x4e,0x58)

// CCalendarPropPage::CCalendarPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CCalendarPropPage

BOOL CCalendarPropPage::CCalendarPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CALENDAR_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, nullptr);
}

// CCalendarPropPage::CCalendarPropPage - Constructor

CCalendarPropPage::CCalendarPropPage() :
	COlePropertyPage(IDD, IDS_CALENDAR_PPG_CAPTION)
{
}

// CCalendarPropPage::DoDataExchange - Moves data between page and properties

void CCalendarPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CCalendarPropPage message handlers
