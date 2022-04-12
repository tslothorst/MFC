
// CntrItem.cpp : implementation of the CMyWordCntrItem class
//

#include "pch.h"
#include "framework.h"
#include "MyWord.h"

#include "MyWordDoc.h"
#include "MyWordView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyWordCntrItem implementation

IMPLEMENT_SERIAL(CMyWordCntrItem, CRichEditCntrItem, 0)

CMyWordCntrItem::CMyWordCntrItem(REOBJECT* preo, CMyWordDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
}

CMyWordCntrItem::~CMyWordCntrItem()
{
	// TODO: add cleanup code here
}


// CMyWordCntrItem diagnostics

#ifdef _DEBUG
void CMyWordCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CMyWordCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

