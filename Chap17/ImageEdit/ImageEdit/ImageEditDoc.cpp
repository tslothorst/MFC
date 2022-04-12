
// ImageEditDoc.cpp : implementation of the CImageEditDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageEdit.h"
#endif

#include "ImageEditDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageEditDoc

IMPLEMENT_DYNCREATE(CImageEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageEditDoc, CDocument)
	ON_COMMAND(ID_EFFECTS_GRAY_SCALE, &CImageEditDoc::OnGrayScale)
	ON_UPDATE_COMMAND_UI(ID_EFFECTS_GRAY_SCALE, &CImageEditDoc::OnUpdateGrayScale)
END_MESSAGE_MAP()


// CImageEditDoc construction/destruction

CImageEditDoc::CImageEditDoc() noexcept : m_event(FALSE, TRUE) // Manual-reset event, initially unowned
{
	m_hThread = NULL;
	m_bWorking = FALSE;

}

CImageEditDoc::~CImageEditDoc()
{
}

BOOL CImageEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}




// CImageEditDoc serialization

void CImageEditDoc::Serialize(CArchive& ar)
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
void CImageEditDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageEditDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageEditDoc::SetSearchContent(const CString& value)
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

// CImageEditDoc diagnostics

#ifdef _DEBUG
void CImageEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageEditDoc commands


void CImageEditDoc::OnGrayScale()
{
	if (!m_bWorking)
	{
		m_bWorking = TRUE;
		m_event.ResetEvent();

		// Package data to pass to the image processing thread
		THREADPARMS* ptp = new THREADPARMS;
		ptp->pWnd = AfxGetMainWnd();
		ptp->pBitmap = &m_bitmap;
		ptp->pPalette = &m_palette;
		ptp->pCriticalSection = &m_cs;
		ptp->pEvent = &m_event;

		// Start the image processing thread and duplicate its handle
		CWinThread* pThread = AfxBeginThread(ThreadFunc, ptp, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

		::DuplicateHandle(GetCurrentProcess(), pThread->m_hThread, GetCurrentProcess(), &m_hThread, 0, FALSE, DUPLICATE_SAME_ACCESS);

		pThread->ResumeThread();
	}
	else
	{
		// Kill the image processing thread
		m_event.SetEvent();
	}
}


void CImageEditDoc::OnUpdateGrayScale(CCmdUI* pCmdUI)
{
	if (m_bWorking)
	{
		pCmdUI->SetText(_T("Stop &Gray Scale Conversion"));
		pCmdUI->Enable();
	}
	else
	{
		pCmdUI->SetText(_T("Convert to &Gray Scale"));
		pCmdUI->Enable((HBITMAP)m_bitmap != NULL);
	}
}


BOOL CImageEditDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// Return now if an image is being processed.
	if (m_bWorking)
	{
		AfxMessageBox(_T("You can't open an image while another is " \
			"being converted"));
		return FALSE;
	}

	// Let the base class do its thing

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


void CImageEditDoc::DeleteContents()
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

CBitmap* CImageEditDoc::GetBitmap()
{
	return ((HBITMAP)m_bitmap == NULL) ? NULL : &m_bitmap;
}

CPalette* CImageEditDoc::GetPalette()
{
	return ((HPALETTE)m_palette == NULL) ? NULL : &m_palette;
}

void CImageEditDoc::ThreadFinished()
{
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;
	m_bWorking = FALSE;

	// Replace the current palette with a gray scale palette
	if ((HPALETTE)m_palette != NULL)
	{
		m_palette.DeleteObject();
		LOGPALETTE* pLP = CreateGrayScale();
		m_palette.CreatePalette(pLP);
		delete[] pLP;
	}

	// Tell the view to repaint
	UpdateAllViews(NULL);
}

void CImageEditDoc::ThreadAborted()
{
	ASSERT(m_hThread != NULL);
	::WaitForSingleObject(m_hThread, INFINITE);
	::CloseHandle(m_hThread);
	m_hThread = NULL;
	m_bWorking = FALSE;
}

// Thread function and other globals
UINT ThreadFunc(LPVOID pParam)
{
	THREADPARMS* ptp = (THREADPARMS*)pParam;
	CWnd* pWnd = ptp->pWnd;
	CBitmap* pBitmap = ptp->pBitmap;
	CPalette* pPalette = ptp->pPalette;
	CCriticalSection* pCriticalSection = ptp->pCriticalSection;
	CEvent* pKillEvent = ptp->pEvent;
	delete ptp;

	DIBSECTION ds;
	pBitmap->GetObject(sizeof(DIBSECTION), &ds);
	int nWidth = ds.dsBm.bmWidth;
	int nHeight = ds.dsBm.bmHeight;

	// Initialize one memory DC (memDC2) to hold a color copy of the
	// image and another memory DC (memDC1) to hold a gray scale copy.
	CClientDC dc(pWnd);
	CBitmap bitmap1;
	CBitmap bitmap2;
	bitmap1.CreateCompatibleBitmap(&dc, nWidth, nHeight);
	bitmap2.CreateCompatibleBitmap(&dc, nWidth, nHeight);

	CDC memDC1;
	CDC memDC2;
	memDC1.CreateCompatibleDC(&dc);
	memDC2.CreateCompatibleDC(&dc);
	CBitmap* pOldBitmap1 = memDC1.SelectObject(&bitmap1);
	CBitmap* pOldBitmap2 = memDC2.SelectObject(&bitmap2);
	CPalette* pOldPalette1 = NULL;
	CPalette* pOldPalette2 = NULL;
	CPalette grayPalette;

	if (pPalette->m_hObject != NULL)
	{
		LOGPALETTE* pLP = CreateGrayScale();
		grayPalette.CreatePalette(pLP);
		delete[] pLP;

		pOldPalette1 = memDC1.SelectPalette(&grayPalette, FALSE);
		pOldPalette2 = memDC2.SelectPalette(pPalette, FALSE);
		memDC1.RealizePalette();
		memDC2.RealizePalette();
	}

	// Coopy the bitmap to memDC2
	CDC memDC3;
	memDC3.CreateCompatibleDC(&dc);
	pCriticalSection->Lock();
	CBitmap* pOldBitmap3 = memDC3.SelectObject(pBitmap);
	memDC2.BitBlt(0, 0, nWidth, nHeight, &memDC3, 0, 0, SRCCOPY);
	memDC3.SelectObject(pOldBitmap3);
	pCriticalSection->Unlock();

	// Convert the colors in memDC2 to shades of gray in memDC1
	int x;
	int y;
	COLORREF crColor;
	BYTE grayLevel;

	for ( y = 0; y < nHeight; y++)
	{
		for (x = 0; x < nWidth; x++) 
		{
			crColor = memDC2.GetPixel(x, y);
			grayLevel = (BYTE)
				(((((UINT)GetRValue(crColor)) * 30) +
					(((UINT)GetGValue(crColor)) * 59) +
					(((UINT)GetBValue(crColor)) * 11)) / 100);
			memDC1.SetPixel(x, y, PALETTERGB(grayLevel, grayLevel, grayLevel));
		}

		// Kill the thread if the pKillEvent event is signaled
		if (::WaitForSingleObject(pKillEvent->m_hObject, 0) == WAIT_OBJECT_0)
		{
			memDC1.SelectObject(pOldBitmap1);
			memDC2.SelectObject(pOldBitmap2);

			if (pPalette->m_hObject != NULL)
			{
				memDC1.SelectPalette(pOldPalette1, FALSE);
				memDC2.SelectPalette(pOldPalette2, FALSE);
			}
			pWnd->PostMessage(WM_USER_THREAD_ABORTED, y + 1, 0);
			return (UINT)-1;
		}
		pWnd->SendMessage(WM_USER_THREAD_UPDATE, y + 1, nHeight);
	}

	// Copy the gray scale image over the original bitmap
	CPalette* pOldPalette3 = NULL;
	if (pPalette->m_hObject != NULL)
	{
		pOldPalette3 = memDC3.SelectPalette(&grayPalette, FALSE);
		memDC3.RealizePalette();
	}
	pCriticalSection->Lock();
	pOldBitmap3 = memDC3.SelectObject(pBitmap);
	memDC3.BitBlt(0, 0, nWidth, nHeight, &memDC1, 0, 0, SRCCOPY);
	memDC3.SelectObject(pOldBitmap3);
	pCriticalSection->Unlock();

	// Clean up the memory DCs
	memDC1.SelectObject(pOldBitmap1);
	memDC2.SelectObject(pOldBitmap2);

	if (pPalette->m_hObject != NULL)
	{
		memDC1.SelectPalette(pOldPalette1, FALSE);
		memDC2.SelectPalette(pOldPalette2, FALSE);
		memDC3.SelectPalette(pOldPalette3, FALSE);
	}

	// Tell the frame window we're done
	pWnd->PostMessage(WM_USER_THREAD_FINISHED, 0, 0);
	return 0;
}

LOGPALETTE* CreateGrayScale()
{
	UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 63);
	LOGPALETTE* pLP = (LOGPALETTE*)new BYTE[nSize];

	pLP->palVersion = 0x300;
	pLP->palNumEntries = 64;

	for (int i = 0; i < 64; i++)
	{
		pLP->palPalEntry[i].peRed = i * 4;
		pLP->palPalEntry[i].peGreen = i * 4;
		pLP->palPalEntry[i].peBlue = i * 4;
		pLP->palPalEntry[i].peFlags = 0;
	}
	return pLP;
}
