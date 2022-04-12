
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Phones.h"
#include "ChildView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CPhoneListBox)
	ON_COMMAND(ID_FILE_NEW, &CChildView::OnNewEntry)
	ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CChildView::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CChildView::OnFileSaveAs)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnNewEntry()
{
	NewEntry();
}


void CChildView::OnFileOpen()
{
	CFileDialog dlg(TRUE, _T("phn"), _T("*.phn"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY);

	if (dlg.DoModal() == IDOK)
	{
		if(LoadFile(dlg.GetPathName()))
		{
			m_strPathName = dlg.GetPathName();
			SetCurSel(0);
		}
	}
}


void CChildView::OnFileSave()
{
	if (!m_strPathName.IsEmpty())
	{
		SaveFile(m_strPathName);
	}
	else // Need a file name first
	{
		OnFileSaveAs();
	}
}


void CChildView::OnFileSaveAs()
{
	CFileDialog dlg(FALSE, _T("phn"), m_strPathName, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY);

	if (dlg.DoModal() == IDOK)
	{
		if(SaveFile(dlg.GetPathName()))
		{
			m_strPathName = dlg.GetPathName();
		}
	}
}

BOOL CChildView::LoadFile(LPCTSTR pszFile)
{
	BOOL bResult = FALSE;

	try
	{
		CStdioFile file(pszFile, CFile::modeRead);
		ResetContent();
		DWORD dwCount;
		file.Read(&dwCount, sizeof(dwCount));
		if (dwCount)
		{
			for (int i = 0; i < (int)dwCount; i++)
			{
				CString string;
				file.ReadString(string);
				AddString(string);
			}
		}
		bResult = TRUE;
	}
	catch (CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}
	return bResult;
}

BOOL CChildView::SaveFile(LPCTSTR pszFile)
{
	BOOL bResult = FALSE;

	try
	{
		CStdioFile file(pszFile, CFile::modeWrite | CFile::modeCreate);
		DWORD dwCount = GetCount();
		file.Write(&dwCount, sizeof(dwCount));
		if (dwCount)
		{
			for (int i = 0; i < (int)dwCount; i++)
			{
				CString string;
				GetText(i, string);
				string += _T('\n');
				file.WriteString(string);
			}
		}
		bResult = TRUE;
	}
	catch (CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}

	return bResult;
}
