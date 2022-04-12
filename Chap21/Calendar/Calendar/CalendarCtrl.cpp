// CalendarCtrl.cpp : Implementation of the CCalendarCtrl ActiveX Control class.

#include "pch.h"
#include "framework.h"
#include "Calendar.h"
#include "CalendarCtrl.h"
#include "CalendarPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CCalendarCtrl, COleControl)

const int CCalendarCtrl::m_nDaysPerMonth[] = {
	31,		// January
	28,		// February
	31,		// March
	30,		// April
	31,		// May
	30,		// June
	31,		// July
	31,		// August
	30,		// September
	31,		// October
	30,		// November
	31,		// December
};

// Message map

BEGIN_MESSAGE_MAP(CCalendarCtrl, COleControl)
	ON_WM_LBUTTONDOWN()
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// Dispatch map

BEGIN_DISPATCH_MAP(CCalendarCtrl, COleControl)
	DISP_PROPERTY_NOTIFY(CCalendarCtrl, "RedSundays", m_bRedSundays, OnRedSundaysChanged, VT_BOOL)
	DISP_FUNCTION(CCalendarCtrl, "GetDate", GetDate, VT_DATE, VTS_NONE)
	DISP_FUNCTION(CCalendarCtrl, "SetDate", SetDate, VT_BOOL, VTS_I2 VTS_I2 VTS_I2)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_FUNCTION_ID(CCalendarCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

// Event map

BEGIN_EVENT_MAP(CCalendarCtrl, COleControl)
	EVENT_CUSTOM("NewDay", FireNewDay, VTS_I2)
END_EVENT_MAP()

// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CCalendarCtrl, 2)
	PROPPAGEID(CCalendarPropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CCalendarCtrl)

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCalendarCtrl, "MFCACTIVEXCONTRO.CalendarCtrl.1",
	0x05910d1c,0x0bba,0x446d,0xa3,0x9f,0x2a,0xe1,0x06,0x47,0xde,0xc3)

// Type library ID and version

IMPLEMENT_OLETYPELIB(CCalendarCtrl, _tlid, _wVerMajor, _wVerMinor)

// Interface IDs

const IID IID_DCalendar = {0x4629000d,0x2924,0x4baa,{0xba,0x77,0x9d,0xaf,0xb0,0x51,0xb4,0x3e}};
const IID IID_DCalendarEvents = {0xe31bff04,0xf4da,0x42ae,{0xa0,0xaf,0xb4,0x3c,0x8d,0x5f,0xb7,0x46}};

// Control type information

static const DWORD _dwCalendarOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCalendarCtrl, IDS_CALENDAR, _dwCalendarOleMisc)

// CCalendarCtrl::CCalendarCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CCalendarCtrl

BOOL CCalendarCtrl::CCalendarCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CALENDAR,
			IDB_CALENDAR,
			afxRegApartmentThreading,
			_dwCalendarOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CCalendarCtrl::CCalendarCtrl - Constructor

CCalendarCtrl::CCalendarCtrl()
{
	InitializeIIDs(&IID_DCalendar, &IID_DCalendarEvents);
	
	CTime time = CTime::GetCurrentTime();
	m_nYear = time.GetYear();
	m_nMonth = time.GetMonth();
	m_nDay = time.GetDay();
}

// CCalendarCtrl::~CCalendarCtrl - Destructor

CCalendarCtrl::~CCalendarCtrl()
{
	// TODO: Cleanup your control's instance data here.
}

// CCalendarCtrl::OnDraw - Drawing function

void CCalendarCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// Paint the control's background
	CBrush brush(TranslateColor(GetBackColor()));
	pdc->FillRect(rcBounds, &brush);

	// Compute the number of days in the month, which day of the week
	// the first of the month falls on, and other information needed to
	// draw the calendar
	int nNumberOfDays = m_nDaysPerMonth[m_nMonth - 1];
	if (m_nMonth == 2 && LeapYear(m_nYear))
	{
		nNumberOfDays++;
	}

	CTime time(m_nYear, m_nMonth, 1, 12, 0, 0);
	int nFirstDayOfMonth = time.GetDayOfWeek();
	int nNumberOfRows = (nNumberOfDays + nFirstDayOfMonth + 5) / 7;

	int nCellWidth = rcBounds.Width() / 7;
	int nCellHeight = rcBounds.Height() / nNumberOfRows;

	int cx = rcBounds.left;
	int cy = rcBounds.top;

	// Draw the calendar rectangle
	CPen* pOldPen = (CPen*)pdc->SelectStockObject(BLACK_PEN);
	CBrush* pOldBrush = (CBrush*)pdc->SelectStockObject(NULL_BRUSH);

	pdc->Rectangle(rcBounds.left, rcBounds.top, rcBounds.left + (7 * nCellWidth), rcBounds.top + (nNumberOfDays * nCellHeight));

	// Draw rectangles representing the days of the month
	CFont font;
	font.CreatePointFont(80, _T("MS Sans Serif"));
	CFont* pOldFont = pdc->SelectObject(&font);

	COLORREF clrOldTextColor = pdc->SetTextColor(RGB(0, 0, 0));
	int nOldBkMode = pdc->SetBkMode(TRANSPARENT);

	for (int i = 0; i < nNumberOfDays; i++)
	{
		int nGridIndex = i + nFirstDayOfMonth - 1;
		int x = ((nGridIndex % 7) * nCellWidth) + cx;
		int y = ((nGridIndex / 7) * nCellHeight) + cy;
		CRect rect(x, y, x + nCellWidth, y + nCellHeight);

		if (i != m_nDay - 1)
		{
			pdc->Draw3dRect(rect, RGB(255, 255, 255), RGB(128, 128, 128));
			pdc->SetTextColor(RGB(0, 0, 0));
		}
		else
		{
			pdc->SelectStockObject(NULL_PEN);
			pdc->SelectStockObject(GRAY_BRUSH);
			pdc->Rectangle(rect);
			pdc->Draw3dRect(rect, RGB(128, 128, 128), RGB(255, 255, 255));
			pdc->SetTextColor(RGB(255, 255, 255));
		}

		CString string;
		string.Format(_T("%d"), i + 1);
		rect.DeflateRect(nCellWidth / 8, nCellHeight / 8);

		if (m_bRedSundays && nGridIndex % 7 == 0)
		{
			pdc->SetTextColor(RGB(255, 0, 0));
		}
		pdc->DrawText(string, rect, DT_SINGLELINE | DT_LEFT | DT_TOP);
	}

	// Clean up and exit
	pdc->SetBkMode(nOldBkMode);
	pdc->SetTextColor(clrOldTextColor);
	pdc->SelectObject(pOldFont);
	pdc->SelectObject(pOldBrush);
	pdc->SelectObject(pOldPen);
}

// CCalendarCtrl::DoPropExchange - Persistence support

void CCalendarCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	PX_Bool(pPX, _T("RedSundays"), m_bRedSundays, TRUE);
}


// CCalendarCtrl::OnResetState - Reset control to default state

void CCalendarCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


// CCalendarCtrl::AboutBox - Display an "About" box to the user

void CCalendarCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_CALENDAR);
	dlgAbout.DoModal();
}


// CCalendarCtrl message handlers

BOOL CCalendarCtrl::LeapYear(int nYear)
{
	return (nYear % 4 == 0) ^ (nYear % 400 == 0) ^ (nYear % 100 == 0);
}

void CCalendarCtrl::OnRedSundaysChanged()
{
	InvalidateControl();
	SetModifiedFlag();
}

DATE CCalendarCtrl::GetDate()
{
	COleDateTime date(m_nYear, m_nMonth, m_nDay, 12, 0, 0);
	return (DATE)date;
}

BOOL CCalendarCtrl::SetDate(short nYear, short nMonth, short nDay)
{
	// Make sure input date is valid
	if (nYear < 1970 || nYear > 2037)
	{
		return FALSE;
	}
	if (nMonth < 1 || nMonth > 12)
	{
		return FALSE;
	}
	int nNumberOfDays = m_nDaysPerMonth[m_nMonth - 1];
	if (nMonth == 2 && LeapYear(nYear))
	{
		nNumberOfDays++;
	}
	if (nDay < 1 || nDay > nNumberOfDays)
	{
		return FALSE;
	}

	// Update the date, repaint the control, and fire a NewDay event
	m_nYear = nYear;
	m_nMonth = nMonth;
	m_nDay = nDay;
	InvalidateControl();

	return TRUE;
}

void CCalendarCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	int nNumberOfDays = m_nDaysPerMonth[m_nMonth - 1];
	if (m_nMonth == 2 && LeapYear(m_nYear))
	{
		nNumberOfDays++;
	}

	CTime time(m_nYear, m_nMonth, 1, 12, 0, 0);
	int nFirstDayOfMonth = time.GetDayOfWeek();
	int nNumberOfRows = (nNumberOfDays + nFirstDayOfMonth + 5) / 7;

	CRect rcClient;
	GetClientRect(&rcClient);
	int nCellWidth = rcClient.Width() / 7;
	int nCellHeight = rcClient.Height() / nNumberOfRows;

	for (int i = 0; i < nNumberOfDays; i++)
	{
		int nGridIndex = i + nFirstDayOfMonth - 1;
		int x = (nGridIndex % 7) * nCellWidth;
		int y = (nGridIndex / 7) * nCellHeight;
		CRect rect(x, y, x + nCellWidth, y + nCellHeight);

		if (rect.PtInRect(point))
		{
			m_nDay = i + 1;
			FireNewDay(m_nDay);
			InvalidateControl();
		}
	}

	COleControl::OnLButtonDown(nFlags, point);
}