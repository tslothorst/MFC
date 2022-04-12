
// VistaDoc.cpp : implementation of the CVistaDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Vista.h"
#endif

#include "VistaDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVistaDoc

IMPLEMENT_DYNCREATE(CVistaDoc, CDocument)

BEGIN_MESSAGE_MAP(CVistaDoc, CDocument)
END_MESSAGE_MAP()


// CVistaDoc construction/destruction

CVistaDoc::CVistaDoc() noexcept
{
}

CVistaDoc::~CVistaDoc()
{
}

BOOL CVistaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}




// CVistaDoc serialization

void CVistaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CVistaDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CVistaDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CVistaDoc::SetSearchContent(const CString& value)
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

// CVistaDoc diagnostics

#ifdef _DEBUG
void CVistaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVistaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CVistaDoc commands


BOOL CVistaDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// Open the file and create a DIB section from its contents
	HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, lpszPathName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (hBitmap == NULL)
	{
		CString string;
		string.Format(_T("%s does not contain a DIB"), lpszPathName);
		AfxMessageBox(string);
		return FALSE;
	}

	m_bitmap.Attach(hBitmap);

	// Return now if this device doesn't support palettes
	CClientDC dc(NULL);
	if ((dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE) == 0)
	{
		return TRUE;
	}

	// Create a palette to go with the DIB section
	if ((HBITMAP)m_bitmap != NULL)
	{
		DIBSECTION ds;
		m_bitmap.GetObject(sizeof(DIBSECTION), &ds);

		int nColors;
		if (ds.dsBmih.biClrUsed != 0)
		{
			nColors = ds.dsBmih.biClrUsed;
		}
		else
		{
			nColors = 1 << ds.dsBmih.biBitCount;
		}

		// Create a halftone palette if the DIB section contains more 
		// than 256 colors
		if (nColors > 256)
		{
			m_palette.CreateHalftonePalette(&dc);
		}

		// Create a custom palette fro mthe DIB section's color table
		// if the number of colors is 256 or less
		else
		{
			RGBQUAD* pRGB = new RGBQUAD[nColors];

			CDC memDC;
			memDC.CreateCompatibleDC(&dc);
			CBitmap* pOldBitmap = memDC.SelectObject(&m_bitmap);
			::GetDIBColorTable((HDC)memDC, 0, nColors, pRGB);
			memDC.SelectObject(pOldBitmap);

			UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * (nColors - 1));
			LOGPALETTE* pLP = (LOGPALETTE*)new BYTE[nSize];

			pLP->palVersion = 0x300;
			pLP->palNumEntries = nColors;

			for (int i = 0; i < nColors; i++)
			{
				pLP->palPalEntry[i].peRed = pRGB[i].rgbRed;
				pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
				pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
				pLP->palPalEntry[i].peFlags = 0;
			}

			m_palette.CreatePalette(pLP);
			delete[] pLP;
			delete[] pRGB;
		}
	}

	return TRUE;
}


void CVistaDoc::DeleteContents()
{
	if ((HBITMAP)m_bitmap != NULL)
	{
		m_bitmap.DeleteObject();
	}
	if ((HPALETTE)m_palette != NULL)
	{
		m_palette.DeleteObject();
	}

	CDocument::DeleteContents();
}

CBitmap* CVistaDoc::GetBitmap()
{
	return ((HBITMAP)m_bitmap == NULL) ? NULL : &m_bitmap;
}

CPalette* CVistaDoc::GetPalette()
{
	return ((HPALETTE)m_palette == NULL) ? NULL : &m_palette;
}