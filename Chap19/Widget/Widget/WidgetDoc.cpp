
// WidgetDoc.cpp : implementation of the CWidgetDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Widget.h"
#endif

#include "WidgetDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWidgetDoc

IMPLEMENT_DYNCREATE(CWidgetDoc, CDocument)

BEGIN_MESSAGE_MAP(CWidgetDoc, CDocument)
END_MESSAGE_MAP()


// CWidgetDoc construction/destruction

CWidgetDoc::CWidgetDoc() noexcept
{
}

CWidgetDoc::~CWidgetDoc()
{
}

BOOL CWidgetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}




// CWidgetDoc serialization

void CWidgetDoc::Serialize(CArchive& ar)
{
	m_arrWidgets.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CWidgetDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CWidgetDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWidgetDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWidgetDoc diagnostics

#ifdef _DEBUG
void CWidgetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWidgetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWidgetDoc commands


void CWidgetDoc::DeleteContents()
{
	int i = m_arrWidgets.GetSize();
	while (i)
	{
		delete m_arrWidgets[--i];
	}
	m_arrWidgets.RemoveAll();
	CDocument::DeleteContents();
}

int CWidgetDoc::GetWidgetCount()
{
	return m_arrWidgets.GetSize();
}

CWidget* CWidgetDoc::GetWidget(int nIndex)
{
	if (nIndex >= m_arrWidgets.GetSize())
	{
		return NULL;
	}
	return (CWidget*)m_arrWidgets[nIndex];
}

int CWidgetDoc::AddWidget(int x, int y, COLORREF color)
{
	int nIndex = -1;
	CWidget* pWidget = NULL;
	try
	{
		pWidget = new CWidget(x, y, color);
		nIndex = m_arrWidgets.Add(pWidget);
		SetModifiedFlag();
	}
	catch (CMemoryException* e)
	{
		AfxMessageBox(_T("Out of memory"));
		if (pWidget != NULL)
		{
			delete pWidget;
		}
		e->Delete();
		return -1;
	}
	return nIndex;
}

BOOL CWidgetDoc::RemoveWidget(int nIndex)
{
	if (nIndex >= m_arrWidgets.GetSize())
	{
		return FALSE;
	}

	delete m_arrWidgets[nIndex];
	m_arrWidgets.RemoveAt(nIndex);
	return TRUE;
}

void CWidgetDoc::OnInsertBlueWidget()
{
	AddWidget(10, 10, RGB(0, 0, 255));
	UpdateAllViews(NULL);
}

void CWidgetDoc::OnInsertRedWidget()
{
	AddWidget(10, 10, RGB(255, 0, 0));
	UpdateAllViews(NULL);
}

void CWidgetDoc::OnInsertYellowWidget()
{
	AddWidget(10, 10, RGB(255, 255, 0));
	UpdateAllViews(NULL);
}