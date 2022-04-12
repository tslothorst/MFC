// Line.cpp : implementation file
//

#include "pch.h"
#include "Sketch.h"
#include "Line.h"


// CLine

IMPLEMENT_SERIAL(CLine, CCmdTarget, 1)
//IMPLEMENT_DYNAMIC(CLine, CCmdTarget)


CLine::CLine()
{
}

CLine::CLine(POINT from, POINT to)
{
	m_ptFrom = from;
	m_ptTo = to;
}

void CLine::Draw(CDC* pDC)
{
	pDC->SelectStockObject(BLACK_PEN);
	pDC->MoveTo(m_ptFrom);
	pDC->LineTo(m_ptTo);
}

CLine::~CLine()
{
}


BEGIN_MESSAGE_MAP(CLine, CCmdTarget)
END_MESSAGE_MAP()



// CLine message handlers

void CLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ptFrom << m_ptTo;
	}
	else
	{
		ar >> m_ptFrom >> m_ptTo;
	}
}