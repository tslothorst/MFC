
// WidgetDoc.h : interface of the CWidgetDoc class
//


#pragma once
#include "WidgetObj.h"
typedef CTypedPtrArray<CObArray, CWidget*> CWidgetArray;

class CWidgetDoc : public CDocument
{
protected: // create from serialization only
	CWidgetDoc() noexcept;
	DECLARE_DYNCREATE(CWidgetDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	BOOL RemoveWidget(int nIndex);
	int AddWidget(int x, int y, COLORREF color);
	CWidget* GetWidget(int nIndex);
	int GetWidgetCount();
	virtual ~CWidgetDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CWidgetArray m_arrWidgets;
// Generated message map functions
protected:
	afx_msg void OnInsertRedWidget();
	afx_msg void OnInsertBlueWidget();
	afx_msg void OnInsertYellowWidget();
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
};
