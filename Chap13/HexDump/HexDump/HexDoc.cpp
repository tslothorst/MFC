
// HexDoc.cpp : implementation of the CHexDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HexDump.h"
#endif

#include "HexDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHexDoc

IMPLEMENT_DYNCREATE(CHexDoc, CDocument)

BEGIN_MESSAGE_MAP(CHexDoc, CDocument)
END_MESSAGE_MAP()


// CHexDoc construction/destruction

CHexDoc::CHexDoc() noexcept
{
	m_nDocLength = 0;
	m_pFileData = NULL;
}

CHexDoc::~CHexDoc()
{
}

BOOL CHexDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

// CHexDoc serialization

void CHexDoc::Serialize(CArchive& ar)
{
	if (ar.IsLoading())
	{
		CFile* pFile = ar.GetFile();
		m_nDocLength = (UINT)pFile->GetLength();

		// Allocate a buffer for the file data.
		try
		{
			m_pFileData = new BYTE[m_nDocLength];
		}
		catch (CMemoryException* e)
		{
			m_nDocLength = 0;
			throw e;
		}

		// Read the file data into the buffer
		try
		{
			pFile->Read(m_pFileData, m_nDocLength);
		}
		catch (CFileException* e)
		{
			delete[] m_pFileData;
			m_pFileData = NULL;
			m_nDocLength = 0;
			throw e;
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CHexDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CHexDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHexDoc::SetSearchContent(const CString& value)
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

// CHexDoc diagnostics

#ifdef _DEBUG
void CHexDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHexDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHexDoc commands


void CHexDoc::DeleteContents()
{
	CDocument::DeleteContents();

	if (m_pFileData != NULL)
	{
		delete[] m_pFileData;
		m_pFileData = NULL;
		m_nDocLength = 0;
	}
}

UINT CHexDoc::GetBytes(UINT nIndex, UINT nCount, PVOID pBuffer)
{
	if (nIndex >= m_nDocLength)
	{
		return 0;
	}

	UINT nLength = nCount;
	if ((nIndex + nCount) > m_nDocLength)
	{
		nLength = m_nDocLength - nIndex;
	}

	::CopyMemory(pBuffer, m_pFileData + nIndex, nLength);

	return nLength;
}

UINT CHexDoc::GetDocumentLength()
{
	return m_nDocLength;
}