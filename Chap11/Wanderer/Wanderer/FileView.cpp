// FileView.cpp : implementation file
//

#include "pch.h"
#include "Wanderer.h"
#include "WandererDoc.h"
#include "FileView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileView

IMPLEMENT_DYNCREATE(CFileView, CListView)

BEGIN_MESSAGE_MAP(CFileView, CListView)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, &CFileView::OnLvnGetdispinfo)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CFileView::OnLvnColumnclick)
	ON_COMMAND(ID_VIEW_LARGE_ICONS, &CFileView::OnViewLargeIcons)
	ON_COMMAND(ID_VIEW_SMALL_ICONS, &CFileView::OnViewSmallIcons)
	ON_COMMAND(ID_VIEW_LIST, &CFileView::OnViewList)
	ON_COMMAND(ID_VIEW_DETAILS, &CFileView::OnViewDetails)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGE_ICONS, &CFileView::OnUpdateViewLargeIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALL_ICONS, &CFileView::OnUpdateViewSmallIcons)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, &CFileView::OnUpdateViewList)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DETAILS, &CFileView::OnUpdateViewDetails)
	ON_COMMAND(ID_FILE_NEW_DIR, &CFileView::OnFileNewDirectory)
END_MESSAGE_MAP()

// CFileView construction/destruction

CFileView::CFileView() noexcept
{
	// TODO: add construction code here

}

CFileView::~CFileView()
{
}

BOOL CFileView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CFileView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// Initialize the image list
	m_ilLarge.Create(IDB_LARGEDOC, 32, 1, RGB(255, 0, 255));
	m_ilSmall.Create(IDB_SMALLDOC, 16, 1, RGB(255, 0, 255));

	GetListCtrl().SetImageList(&m_ilLarge, LVSIL_NORMAL);
	GetListCtrl().SetImageList(&m_ilSmall, LVSIL_SMALL);

	// Add colums to the list view
	GetListCtrl().InsertColumn(0, _T("File Name"), LVCFMT_LEFT, 192);
	GetListCtrl().InsertColumn(1, _T("Size"), LVCFMT_RIGHT, 96);
	GetListCtrl().InsertColumn(2, _T("Last Modified"), LVCFMT_CENTER, 128);

	// Populate the list view with items
	TCHAR szPath[MAX_PATH];
	::GetCurrentDirectory(sizeof(szPath) / sizeof(TCHAR), szPath);
	Refresh(szPath);
}


// CFileView diagnostics

#ifdef _DEBUG
void CFileView::AssertValid() const
{
	CListView::AssertValid();
}

void CFileView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CWandererDoc* CFileView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWandererDoc)));
	return (CWandererDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileView message handlers

int CFileView::Refresh(LPCTSTR pszPath)
{
	CString strPath = pszPath;
	if (strPath.Right(1) != _T("\\"))
	{
		strPath += _T("\\");
	}
	strPath += _T("*.*");

	HANDLE hFind;
	WIN32_FIND_DATA fd;
	int nCount = 0;

	if ((hFind = ::FindFirstFile(strPath, &fd)) != INVALID_HANDLE_VALUE)
	{
		// Delete existing items (if any)
		GetListCtrl().DeleteAllItems();

		// Show the path name in the frame window's title bar
		TCHAR szFullPath[MAX_PATH];
		::GetFullPathName(pszPath, sizeof(szFullPath) / sizeof(TCHAR), szFullPath, NULL);
		m_strPath = szFullPath;

		CString strTitle = _T("WinDir - ");
		strTitle += szFullPath;
		AfxGetMainWnd()->SetWindowText(strTitle);

		// Add item representing files ot the list view
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			AddItem(nCount++, &fd);
		}

		while (::FindNextFile(hFind, &fd))
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (!AddItem(nCount++, &fd))
				{
					break;
				}
			}
		}

		::FindClose(hFind);
	}

	return nCount;
}

BOOL CFileView::AddItem(int nIndex, WIN32_FIND_DATA* pfd)
{
	// Allocate a new ITEMINFO structure and initialize it with information
	// about the item
	ITEMINFO* pItem;
	try
	{
		pItem = new ITEMINFO;
	}
	catch (CMemoryException* e)
	{
		e->Delete();
		return FALSE;
	}

	pItem->strFileName = pfd->cFileName;
	pItem->nFileSizeLow = pfd->nFileSizeLow;
	pItem->ftLastWriteTime = pfd->ftLastWriteTime;

	// Add the item to the list view
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvi.iItem = nIndex;
	lvi.iSubItem = 0;
	lvi.iImage = 0;
	lvi.pszText = LPSTR_TEXTCALLBACK;
	lvi.lParam = (LPARAM)pItem;

	if (GetListCtrl().InsertItem(&lvi) == -1)
	{
		return FALSE;
	}
	return TRUE;
}

void CFileView::FreeItemMemory()
{
	int nCount = GetListCtrl().GetItemCount();
	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			delete (ITEMINFO*)GetListCtrl().GetItemData(i);
		}
	}
}

void CFileView::OnDraw(CDC* pDC)
{
	CWandererDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CFileView::OnDestroy()
{
	FreeItemMemory();
	CListView::OnDestroy();
}


void CFileView::OnLvnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString string;
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

	if (pDispInfo->item.mask & LVIF_TEXT)
	{
		ITEMINFO* pItem = (ITEMINFO*)pDispInfo->item.lParam;

		switch (pDispInfo->item.iSubItem)
		{
		case 0: // Filename
			::lstrcpy(pDispInfo->item.pszText, pItem->strFileName);
			break;
		case 1: // File size
			string.Format(_T("%u"), pItem->nFileSizeLow);
			::lstrcpy(pDispInfo->item.pszText, string);
			break;
		case 2: // Date and time
			CTime time(pItem->ftLastWriteTime);

			BOOL pm = FALSE;
			int nHour = time.GetHour();
			if (nHour == 0)
			{
				nHour = 12;
			}
			else if (nHour == 12)
			{
				pm = TRUE;
			}
			else if (nHour > 12)
			{
				nHour -= 12;
				pm = TRUE;
			}

			string.Format(_T("%d%0.2d%0.2d(%d:%0.2d%c)"), time.GetMonth(), time.GetDay(), time.GetYear() % 100, nHour, time.GetMinute(), pm ? _T('p') : _T('a'));
			::lstrcpy(pDispInfo->item.pszText, string);
			break;
		}
	}

	*pResult = 0;
}


void CFileView::OnLvnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	GetListCtrl().SortItems(CompareFunc, pNMLV->iSubItem);
	*pResult = 0;
}

int CFileView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	ITEMINFO* pItem1 = (ITEMINFO*)lParam1;
	ITEMINFO* pItem2 = (ITEMINFO*)lParam2;
	int nResult;

	switch (lParamSort)
	{
	case 0: // Filename
		nResult = pItem1->strFileName.CompareNoCase(pItem2->strFileName);
		break;
	case 1: // File size
		nResult = pItem1->nFileSizeLow - pItem2->nFileSizeLow;
		break;
	case 2: // Date and time
		nResult = ::CompareFileTime(&pItem1->ftLastWriteTime, &pItem2->ftLastWriteTime);
		break;
	}
	return nResult;
}

void CFileView::OnViewLargeIcons()
{
	ModifyStyle(LVS_TYPEMASK, LVS_ICON);
}


void CFileView::OnViewSmallIcons()
{
	ModifyStyle(LVS_TYPEMASK, LVS_SMALLICON);
}


void CFileView::OnViewList()
{
	ModifyStyle(LVS_TYPEMASK, LVS_LIST);
}


void CFileView::OnViewDetails()
{
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
}


void CFileView::OnUpdateViewLargeIcons(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_ICON);
}


void CFileView::OnUpdateViewSmallIcons(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_SMALLICON);
}


void CFileView::OnUpdateViewList(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_LIST);
}


void CFileView::OnUpdateViewDetails(CCmdUI* pCmdUI)
{
	DWORD dwCurrentStyle = GetStyle() & LVS_TYPEMASK;
	pCmdUI->SetRadio(dwCurrentStyle == LVS_REPORT);
}


void CFileView::OnFileNewDirectory()
{
	//CPathDialog dlg;
	//dlg.m_strPath = m_strPath;
	//if (dlg.DoModal() == IDOK)
	//{
	//	Refresh(dlg.m_strPath);
	//}
}