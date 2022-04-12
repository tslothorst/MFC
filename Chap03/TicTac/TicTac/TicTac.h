#pragma once
#include <afxwin.h>

class CTicTacApp : public CWinApp 
{
public:
	virtual BOOL InitInstance();
};

class CMainWindow : public CWnd 
{
public:
	CMainWindow();
protected:
	static constexpr int ex = 1;
	static constexpr int oh = 2;

	static const CRect m_rcSquares[9];	// Grid coordinates
	int m_nGameGrid[9];					// Grid contents
	int m_nNextChar;					// Next character (ex or oh)
	int GetRectID(CPoint point);
	void DrawBoard(CDC* pDC);
	void DrawX(CDC* pDC, int nPos);
	void DrawO(CDC* pDC, int nPos);
	void ResetGame();
	void CheckForGameOver();
	int IsWinner();
	BOOL IsDraw();

	virtual void PostNcDestroy();

	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};