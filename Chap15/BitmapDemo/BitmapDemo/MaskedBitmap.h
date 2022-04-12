#pragma once

// CMaskedBitmap command target

class CMaskedBitmap : public CBitmap
{
public:
	CMaskedBitmap();
	virtual ~CMaskedBitmap();
	void DrawTransparent(CDC* pDC, int x, int y, COLORREF clrTransparency);
	void Draw(CDC* pDC, int x, int y);
};


