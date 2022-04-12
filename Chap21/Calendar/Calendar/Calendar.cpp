// Calendar.cpp : Implementation of CCalendarApp and DLL registration.

#include "pch.h"
#include "framework.h"
#include "Calendar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCalendarApp theApp;

const GUID CDECL _tlid = {0xab7f3116,0x70ca,0x408f,{0xa8,0x38,0x6d,0x4b,0x6b,0xf3,0x96,0x9a}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CCalendarApp::InitInstance - DLL initialization

BOOL CCalendarApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CCalendarApp::ExitInstance - DLL termination

int CCalendarApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
