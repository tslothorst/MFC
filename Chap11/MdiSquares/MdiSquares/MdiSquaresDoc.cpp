
// MdiSquaresDoc.cpp : implementation of the CMdiSquaresDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MdiSquares.h"
#endif

#include "MdiSquaresDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMdiSquaresDoc

IMPLEMENT_DYNCREATE(CMdiSquaresDoc, CDocument)

BEGIN_MESSAGE_MAP(CMdiSquaresDoc, CDocument)
	ON_COMMAND(ID_COLOR_RED, &CMdiSquaresDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_YELLOW, &CMdiSquaresDoc::OnColorYellow)
	ON_COMMAND(ID_COLOR_GREEN, &CMdiSquaresDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_CYAN, &CMdiSquaresDoc::OnColorCyan)
	ON_COMMAND(ID_COLOR_BLUE, &CMdiSquaresDoc::OnColorBlue)
	ON_COMMAND(ID_COLOR_WHITE, &CMdiSquaresDoc::OnColorWhite)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CMdiSquaresDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, &CMdiSquaresDoc::OnUpdateColorYellow)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CMdiSquaresDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_CYAN, &CMdiSquaresDoc::OnUpdateColorCyan)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CMdiSquaresDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_WHITE, &CMdiSquaresDoc::OnUpdateColorWhite)
END_MESSAGE_MAP()


// CMdiSquaresDoc construction/destruction

CMdiSquaresDoc::CMdiSquaresDoc() noexcept
{
}

CMdiSquaresDoc::~CMdiSquaresDoc()
{
}

BOOL CMdiSquaresDoc::OnNewDocument()
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




// CMdiSquaresDoc serialization

void CMdiSquaresDoc::Serialize(CArchive& ar)
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
void CMdiSquaresDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMdiSquaresDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMdiSquaresDoc::SetSearchContent(const CString& value)
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

// CMdiSquaresDoc diagnostics

#ifdef _DEBUG
void CMdiSquaresDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMdiSquaresDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMdiSquaresDoc commands
COLORREF CMdiSquaresDoc::GetCurrentColor()
{
	return m_clrCurrentColor;
}

COLORREF CMdiSquaresDoc::GetSquare(int i, int j)
{
	ASSERT(i >= 0 && 1 <= 3 && j >= 0 && j <= 3);
	return m_clrGrid[i][j];
}

void CMdiSquaresDoc::SetSquare(int i, int j, COLORREF color)
{
	ASSERT(i >= 0 && i <= 3 && j >= 0 && j <= 3);
	m_clrGrid[i][j] = color;
	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);
}

void CMdiSquaresDoc::OnColorRed()
{
	m_clrCurrentColor = RGB(255, 0, 0);
}


void CMdiSquaresDoc::OnColorYellow()
{
	m_clrCurrentColor = RGB(255, 255, 0);
}


void CMdiSquaresDoc::OnColorGreen()
{
	m_clrCurrentColor = RGB(0, 255, 0);
}


void CMdiSquaresDoc::OnColorCyan()
{
	m_clrCurrentColor = RGB(0, 255, 255);
}


void CMdiSquaresDoc::OnColorBlue()
{
	m_clrCurrentColor = RGB(0, 0, 255);
}


void CMdiSquaresDoc::OnColorWhite()
{
	m_clrCurrentColor = RGB(255, 255, 255);
}


void CMdiSquaresDoc::OnUpdateColorRed(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 0, 0));
}


void CMdiSquaresDoc::OnUpdateColorYellow(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 0));
}


void CMdiSquaresDoc::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 0));
}


void CMdiSquaresDoc::OnUpdateColorCyan(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 255));
}


void CMdiSquaresDoc::OnUpdateColorBlue(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 0, 255));
}


void CMdiSquaresDoc::OnUpdateColorWhite(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 255));
}
