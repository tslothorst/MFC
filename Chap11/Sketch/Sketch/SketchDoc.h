
// SketchDoc.h : interface of the CSketchDoc class
//


#pragma once
#include "Line.h"
typedef CTypedPtrArray<CObArray, CLine*> CLineArray;

class CSketchDoc : public CDocument
{
protected: // create from serialization only
	CSketchDoc() noexcept;
	DECLARE_DYNCREATE(CSketchDoc)

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
	CLine* GetLine(int nIndex);
	int GetLineCount();
	CLine* AddLine(POINT from, POINT to);
	BOOL IsGridVisible();
	virtual ~CSketchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CLineArray m_arrLines;
	BOOL m_bShowGrid;
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
protected:
	virtual void DeleteContents();
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
};
