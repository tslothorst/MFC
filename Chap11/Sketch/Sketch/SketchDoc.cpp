
// SketchDoc.cpp : implementation of the CSketchDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketch.h"
#endif

#include "SketchDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketchDoc

IMPLEMENT_DYNCREATE(CSketchDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketchDoc, CDocument)
	ON_COMMAND(ID_VIEW_GRID, &CSketchDoc::OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, &CSketchDoc::OnUpdateViewGrid)
END_MESSAGE_MAP()


// CSketchDoc construction/destruction

CSketchDoc::CSketchDoc() noexcept
{
	// TODO: add one-time construction code here

}

CSketchDoc::~CSketchDoc()
{
}

BOOL CSketchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_bShowGrid = TRUE;

	return TRUE;
}




// CSketchDoc serialization

void CSketchDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_bShowGrid;
	}
	else
	{
		ar >> m_bShowGrid;
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSketchDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CSketchDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketchDoc::SetSearchContent(const CString& value)
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

// CSketchDoc diagnostics

#ifdef _DEBUG
void CSketchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketchDoc commands

BOOL CSketchDoc::IsGridVisible()
{
	return m_bShowGrid;
}

void CSketchDoc::DeleteContents()
{
	int nCount = GetLineCount();

	if (nCount)
	{
		for (int i = 0; i < nCount; i++)
		{
			delete m_arrLines[i];
		}

		m_arrLines.RemoveAll();
	}

	CDocument::DeleteContents();
}


void CSketchDoc::OnViewGrid()
{
	if (m_bShowGrid)
	{
		m_bShowGrid = FALSE;
	}
	else
	{
		m_bShowGrid = TRUE;
	}

	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}


void CSketchDoc::OnUpdateViewGrid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowGrid);
}

CLine* CSketchDoc::AddLine(POINT from, POINT to)
{
	CLine* pLine = NULL;

	try
	{
		pLine = new CLine(from, to);
		m_arrLines.Add(pLine);
		SetModifiedFlag(TRUE);
		UpdateAllViews(NULL, 0x7C, pLine);
	}
	catch (CMemoryException* e)
	{
		AfxMessageBox(_T("Out of memory"));
		if (pLine != NULL)
		{
			delete pLine;
			pLine = NULL;
		}

		e->Delete();
	}
	return pLine;
}

int CSketchDoc::GetLineCount()
{
	return m_arrLines.GetSize();
}

CLine* CSketchDoc::GetLine(int nIndex)
{
	ASSERT(nIndex < GetLineCount());
	return m_arrLines[nIndex];
}