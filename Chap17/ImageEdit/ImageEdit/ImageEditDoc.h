
// ImageEditDoc.h : interface of the CImageEditDoc class
//


#pragma once
UINT ThreadFunc(LPVOID pParam);
LOGPALETTE* CreateGrayScale();

class CImageEditDoc : public CDocument
{
protected: // create from serialization only
	CImageEditDoc() noexcept;
	DECLARE_DYNCREATE(CImageEditDoc)

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
	void ThreadAborted();
	void ThreadFinished();
	CPalette* GetPalette();
	CBitmap* GetBitmap();
	virtual ~CImageEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
protected:
	afx_msg void OnGrayScale();
	afx_msg void OnUpdateGrayScale(CCmdUI* pCmdUI);
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();	
protected:
	BOOL m_bWorking;
	CCriticalSection m_cs;
	CEvent m_event;
	HANDLE m_hThread;	
	CPalette m_palette;
	CBitmap m_bitmap;
};
