
// SdiSquaresDoc.cpp : implementation of the CSdiSquaresDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SdiSquares.h"
#endif

#include "SdiSquaresDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSdiSquaresDoc

IMPLEMENT_DYNCREATE(CSdiSquaresDoc, CDocument)

BEGIN_MESSAGE_MAP(CSdiSquaresDoc, CDocument)
	ON_COMMAND(ID_COLOR_RED, &CSdiSquaresDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_YELLOW, &CSdiSquaresDoc::OnColorYellow)
	ON_COMMAND(ID_COLOR_GREEN, &CSdiSquaresDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_CYAN, &CSdiSquaresDoc::OnColorCyan)
	ON_COMMAND(ID_COLOR_BLUE, &CSdiSquaresDoc::OnColorBlue)
	ON_COMMAND(ID_COLOR_WHITE, &CSdiSquaresDoc::OnColorWhite)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSdiSquaresDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, &CSdiSquaresDoc::OnUpdateColorYellow)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSdiSquaresDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_CYAN, &CSdiSquaresDoc::OnUpdateColorCyan)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSdiSquaresDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_WHITE, &CSdiSquaresDoc::OnUpdateColorWhite)
END_MESSAGE_MAP()


// CSdiSquaresDoc construction/destruction

CSdiSquaresDoc::CSdiSquaresDoc() noexcept
{
	// TODO: add one-time construction code here

}

CSdiSquaresDoc::~CSdiSquaresDoc()
{
}

BOOL CSdiSquaresDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_clrGrid[i][j] = RGB(255, 0, 0);
		}
	}

	return TRUE;
}




// CSdiSquaresDoc serialization

void CSdiSquaresDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ar << m_clrGrid[i][j];
			}
		}

		ar << m_clrCurrentColor;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ar >> m_clrGrid[i][j];
			}
		}

		ar >> m_clrCurrentColor;
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSdiSquaresDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CSdiSquaresDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSdiSquaresDoc::SetSearchContent(const CString& value)
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

// CSdiSquaresDoc diagnostics

#ifdef _DEBUG
void CSdiSquaresDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSdiSquaresDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSdiSquaresDoc commands

COLORREF CSdiSquaresDoc::GetCurrentColor()
{
	return m_clrCurrentColor;
}

COLORREF CSdiSquaresDoc::GetSquare(int i, int j)
{
	ASSERT(i >= 0 && 1 <= 3 && j >= 0 && j <= 3);
	return m_clrGrid[i][j];
}

void CSdiSquaresDoc::SetSquare(int i, int j, COLORREF color)
{
	ASSERT(i >= 0 && i <= 3 && j >= 0 && j <= 3);
	m_clrGrid[i][j] = color;
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}

void CSdiSquaresDoc::OnColorRed()
{
	m_clrCurrentColor = RGB(255, 0, 0);
}


void CSdiSquaresDoc::OnColorYellow()
{
	m_clrCurrentColor = RGB(255, 255, 0);
}


void CSdiSquaresDoc::OnColorGreen()
{
	m_clrCurrentColor = RGB(0, 255, 0);
}


void CSdiSquaresDoc::OnColorCyan()
{
	m_clrCurrentColor = RGB(0, 255, 255);
}


void CSdiSquaresDoc::OnColorBlue()
{
	m_clrCurrentColor = RGB(0, 0, 255);
}


void CSdiSquaresDoc::OnColorWhite()
{
	m_clrCurrentColor = RGB(255, 255, 255);
}


void CSdiSquaresDoc::OnUpdateColorRed(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 0, 0));
}


void CSdiSquaresDoc::OnUpdateColorYellow(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 0));
}


void CSdiSquaresDoc::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 0));
}


void CSdiSquaresDoc::OnUpdateColorCyan(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 255));
}


void CSdiSquaresDoc::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 0, 255));
}


void CSdiSquaresDoc::OnUpdateColorWhite(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 255));
}
