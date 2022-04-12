#pragma once

// CWidget command target

class CWidget : public CObject
{
	DECLARE_SERIAL(CWidget)

	// Attributes
public:

	// Operations
public:
	CWidget();
	CWidget(int x, int y, COLORREF color);
	virtual ~CWidget();
	void DrawSelected(CDC* pDC);
	BOOL PtInWidget(POINT point);
	virtual void DrawDragImage(CDC* pDC, POINT point);
	virtual void Draw(CDC* pDC);
	COLORREF GetColor();
	CRect GetRect();

	// Overrides
	virtual void Serialize(CArchive& ar);

	// Implementation
protected:
	COLORREF m_color;
	CRect m_rect;
};


