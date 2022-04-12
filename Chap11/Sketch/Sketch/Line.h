
#pragma once


// CLine command target

class CLine : public CCmdTarget
{
	DECLARE_SERIAL(CLine)
	/*DECLARE_DYNAMIC(CLine)*/

public:
	CLine();
	CLine(POINT from, POINT to);
	void Draw(CDC* pDC);
	virtual void Serialize(CArchive& ar);
	virtual ~CLine();

protected:
	CPoint m_ptFrom;
	CPoint m_ptTo;
	DECLARE_MESSAGE_MAP()
};


