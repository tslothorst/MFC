#pragma once
#include <afxwin.h>

class CVisualKBApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CWnd
{
public:
	CMainWindow();
protected:
	static constexpr int max_string = 12;

	int m_cxChar;								// Average character width
	int m_cyChar;								// Character height
	int m_cyLine;								// Vertical line spacing in messsage box
	int m_nTextPos;								// Index of current character in text box
	int m_nTabStops[7];							// Tab stop locations for tabbed output
	int m_nTextLimit;							// Maximum width of text in the textbox
	int m_nMsgPos;								// Current position in m_strMessages array

	HCURSOR m_hCursorArrow;						// Handle of arrow cursor
	HCURSOR m_hCursorIBeam;						// Handle of I-beam cursor

	CPoint m_ptTextOrigin;						// Origin for drawing input text
	CPoint m_ptHeaderOrigin;					// Origin for drawing header text
	CPoint m_ptUpperMsgOrigin;					// Origin of first line in message box
	CPoint m_ptLowerMsgOrigin;					// Origin of last line in message box
	CPoint m_ptCaretPos;						// Current caret position

	CRect m_rcTextBox;							// Coordinates of the textbox
	CRect m_rcTextBoxBorder;					// Coordinates of text box border
	CRect m_rcMsgBoxBorder;						// Coordinates of message box border
	CRect m_rcScroll;							// Coordinates of scroll rectangle

	CString m_strInputText;						// Input array
	CString m_strMessages[max_string];			// Array of message strings

	int GetNearestPos(CPoint point);
	void PositionCaret(CDC* pDC = NULL);
	void DrawInputText(CDC* pDC);
	void ShowMessage(LPCTSTR pszMessage, UINT nChar, UINT nRepCnt, UINT nFlags);
	void DrawMessageHeader(CDC* pDC);
	void DrawMessages(CDC* pDC);

	virtual void PostNcDestroy();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pWnd);
	afx_msg void OnKillFocus(CWnd* pWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};