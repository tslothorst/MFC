
// AutoMathDoc.cpp : implementation of the CAutoMathDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "AutoMath.h"
#endif

#include "AutoMathDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAutoMathDoc

IMPLEMENT_DYNCREATE(CAutoMathDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoMathDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoMathDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_IAutoMath to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {5bc9d67a-55e1-4548-b786-8ed007bb65ad}
static const IID IID_IAutoMath =
{0x5bc9d67a,0x55e1,0x4548,{0xb7,0x86,0x8e,0xd0,0x07,0xbb,0x65,0xad}};

BEGIN_INTERFACE_MAP(CAutoMathDoc, CDocument)
	INTERFACE_PART(CAutoMathDoc, IID_IAutoMath, Dispatch)
END_INTERFACE_MAP()


// CAutoMathDoc construction/destruction

CAutoMathDoc::CAutoMathDoc() noexcept
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CAutoMathDoc::~CAutoMathDoc()
{
	AfxOleUnlockApp();
}

BOOL CAutoMathDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CAutoMathDoc serialization

void CAutoMathDoc::Serialize(CArchive& ar)
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
void CAutoMathDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CAutoMathDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CAutoMathDoc::SetSearchContent(const CString& value)
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

// CAutoMathDoc diagnostics

#ifdef _DEBUG
void CAutoMathDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoMathDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAutoMathDoc commands


long CAutoMathDoc::Add(long a, long b)
{
	return a + b;
}


long CAutoMathDoc::Subtract(long a, long b)
{
	return a - b;
}
