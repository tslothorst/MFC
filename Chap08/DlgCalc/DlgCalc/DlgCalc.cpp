
// DlgCalc.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "DlgCalc.h"
#include "DlgCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDlgCalcApp

BEGIN_MESSAGE_MAP(CDlgCalcApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDlgCalcApp construction

CDlgCalcApp::CDlgCalcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDlgCalcApp object

CDlgCalcApp theApp;


// CDlgCalcApp initialization

BOOL CDlgCalcApp::InitInstance()
{
	CWinApp::InitInstance();


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CDlgCalcDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

