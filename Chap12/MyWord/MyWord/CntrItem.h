
// CntrItem.h : interface of the CMyWordCntrItem class
//

#pragma once

class CMyWordDoc;
class CMyWordView;

class CMyWordCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CMyWordCntrItem)

// Constructors
public:
	CMyWordCntrItem(REOBJECT* preo = nullptr, CMyWordDoc* pContainer = nullptr);
		// Note: pContainer is allowed to be null to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-null document pointer

// Attributes
public:
	CMyWordDoc* GetDocument()
		{ return reinterpret_cast<CMyWordDoc*>(CRichEditCntrItem::GetDocument()); }
	CMyWordView* GetActiveView()
		{ return reinterpret_cast<CMyWordView*>(CRichEditCntrItem::GetActiveView()); }

// Implementation
public:
	~CMyWordCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

