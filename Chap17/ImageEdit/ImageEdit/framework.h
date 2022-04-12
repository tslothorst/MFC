#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars

#define WM_USER_UPDATE_STATS		WM_USER + 0X100
#define WM_USER_THREAD_UPDATE		WM_USER + 0X101
#define WM_USER_THREAD_FINISHED		WM_USER + 0X102
#define WM_USER_THREAD_ABORTED		WM_USER + 0X103

typedef struct tagTHREADPARMS {
	CWnd* pWnd;
	CBitmap* pBitmap;
	CPalette* pPalette;
	CCriticalSection* pCriticalSection;
	CEvent* pEvent;
} THREADPARMS;











