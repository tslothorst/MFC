
// MyWordView.cpp : implementation of the CMyWordView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyWord.h"
#endif

#include "MyWordDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "MyWordView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyWordView

IMPLEMENT_DYNCREATE(CMyWordView, CRichEditView)

BEGIN_MESSAGE_MAP(CMyWordView, CRichEditView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_CHAR_BOLD, &CMyWordView::OnCharBold)
	ON_COMMAND(ID_CHAR_ITALIC, &CMyWordView::OnCharItalic)
	ON_COMMAND(ID_CHAR_UNDERLINE, &CMyWordView::OnCharUnderline)
	ON_COMMAND(ID_PARA_LEFT, &CMyWordView::OnParaLeft)
	ON_COMMAND(ID_PARA_CENTER, &CMyWordView::OnParaCenter)
	ON_COMMAND(ID_PARA_RIGHT, &CMyWordView::OnParaRight)
	ON_UPDATE_COMMAND_UI(ID_CHAR_BOLD, &CMyWordView::OnUpdateCharBold)
	ON_UPDATE_COMMAND_UI(ID_CHAR_ITALIC, &CMyWordView::OnUpdateCharItalic)
	ON_UPDATE_COMMAND_UI(ID_CHAR_UNDERLINE, &CMyWordView::OnUpdateCharUnderline)
	ON_UPDATE_COMMAND_UI(ID_PARA_LEFT, &CMyWordView::OnUpdateParaLeft)
	ON_UPDATE_COMMAND_UI(ID_PARA_CENTER, &CMyWordView::OnUpdateParaCenter)
	ON_UPDATE_COMMAND_UI(ID_PARA_RIGHT, &CMyWordView::OnUpdateParaRight)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, &CMyWordView::OnUpdateLineNumber)
END_MESSAGE_MAP()

// CMyWordView construction/destruction

CMyWordView::CMyWordView() noexcept
{
}

CMyWordView::~CMyWordView()
{
}

BOOL CMyWordView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CRichEditView::PreCreateWindow(cs);
}

void CMyWordView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	CHARFORMAT2 cf;
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_PROTECTED | CFM_STRIKEOUT | CFM_FACE | CFM_SIZE;
	cf.dwEffects = 0;
	cf.yHeight = 240; // 240 twips == 12 points

	::lstrcpy(cf.szFaceName, _T("Times New Roman"));
	SetCharFormat(cf);

}

void CMyWordView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != nullptr && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == nullptr);
   }
   CRichEditView::OnDestroy();
}



// CMyWordView diagnostics

#ifdef _DEBUG
void CMyWordView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CMyWordView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CMyWordDoc* CMyWordView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyWordDoc)));
	return (CMyWordDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyWordView message handlers


void CMyWordView::OnCharBold()
{
	CHARFORMAT2 cf;
	cf = GetCharFormatSelection();
	if (!(cf.dwMask & CFM_BOLD) || !(cf.dwEffects & CFE_BOLD))
	{
		cf.dwEffects = CFE_BOLD;
	}
	else
	{
		cf.dwEffects = 0;
	}

	cf.dwMask = CFM_BOLD;
	SetCharFormat(cf);
}


void CMyWordView::OnCharItalic()
{
	CHARFORMAT2 cf;
	cf = GetCharFormatSelection();
	if (!(cf.dwMask & CFM_ITALIC) || !(cf.dwEffects & CFE_ITALIC))
	{
		cf.dwEffects = CFE_ITALIC;
	}
	else
	{
		cf.dwEffects = 0;
	}

	cf.dwMask = CFM_ITALIC;
	SetCharFormat(cf);
}


void CMyWordView::OnCharUnderline()
{
	CHARFORMAT2 cf;
	cf = GetCharFormatSelection();
	if (!(cf.dwMask & CFM_UNDERLINE) || !(cf.dwEffects & CFE_UNDERLINE))
	{
		cf.dwEffects = CFE_UNDERLINE;
	}
	else
	{
		cf.dwEffects = 0;
	}

	cf.dwMask = CFM_UNDERLINE;
	SetCharFormat(cf);
}


void CMyWordView::OnParaLeft()
{
	OnParaAlign(PFA_LEFT);
}


void CMyWordView::OnParaCenter()
{
	OnParaAlign(PFA_CENTER);
}


void CMyWordView::OnParaRight()
{
	OnParaAlign(PFA_RIGHT);
}


void CMyWordView::OnUpdateCharBold(CCmdUI* pCmdUI)
{
	OnUpdateCharEffect(pCmdUI, CFM_BOLD, CFE_BOLD);
}


void CMyWordView::OnUpdateCharItalic(CCmdUI* pCmdUI)
{
	OnUpdateCharEffect(pCmdUI, CFM_ITALIC, CFE_ITALIC);
}


void CMyWordView::OnUpdateCharUnderline(CCmdUI* pCmdUI)
{
	OnUpdateCharEffect(pCmdUI, CFM_UNDERLINE, CFE_UNDERLINE);
}


void CMyWordView::OnUpdateParaLeft(CCmdUI* pCmdUI)
{
	OnUpdateParaAlign(pCmdUI, PFA_LEFT);
}


void CMyWordView::OnUpdateParaCenter(CCmdUI* pCmdUI)
{
	OnUpdateParaAlign(pCmdUI, PFA_CENTER);
}


void CMyWordView::OnUpdateParaRight(CCmdUI* pCmdUI)
{
	OnUpdateParaAlign(pCmdUI, PFA_RIGHT);
}


void CMyWordView::OnUpdateLineNumber(CCmdUI* pCmdUI)
{
	int nLine = GetRichEditCtrl().LineFromChar(-1) + 1;

	CString string;
	string.Format(_T("Line %d"), nLine);
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(string);
}

void CMyWordView::ChangeFont(LPCTSTR pszFaceName)
{
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_FACE;
	::lstrcpy(cf.szFaceName, pszFaceName);
	SetCharFormat(cf);
}

void CMyWordView::ChangeFontSize(int nSize)
{
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(CHARFORMAT2);
	cf.dwMask = CFM_SIZE;
	cf.yHeight = nSize;
	SetCharFormat(cf);
}

void CMyWordView::GetFontInfo(LPTSTR pszFaceName, int& nSize)
{
	CHARFORMAT2 cf = GetCharFormatSelection();
	::lstrcpy(pszFaceName, cf.dwMask & CFM_FACE ? cf.szFaceName : _T(""));
	nSize = cf.dwMask & CFM_SIZE ? cf.yHeight : -1;
}