#include "TicTac.h"

CTicTacApp TicTac;

BOOL CTicTacApp::InitInstance() 
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	END_MESSAGE_MAP()

const CRect CMainWindow::m_rcSquares[9] =
{
	CRect(16,16,112,112),
	CRect(128,16,224,112),
	CRect(16,128,112,224),
	CRect(128,128,224,224),
	CRect(240,128,336,224),
	CRect(16,240,112,336),
	CRect(128,240,224,336),
	CRect(240,240,336,336)
};

CMainWindow::CMainWindow()
{
	m_nNextChar = ex;
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));

	// Register a WNDCLASS
	CString strWndClass = AfxRegisterWndClass(
		CS_DBLCLKS,											// Class style
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),			// Class cursor
		(HBRUSH)(COLOR_3DFACE + 1),							// Background brush
		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO)			// Class icon
	);

	// Create a window
	CreateEx(0, strWndClass, _T("Tic-Tac-Toe"), WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);

	//Size the window
	CRect rect(0, 0, 352, 352);
	CalcWindowRect(&rect);
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
}

void CMainWindow::PostNcDestroy()
{
	delete this;
}

void CMainWindow::OnPaint() 
{
	CPaintDC dc(this);
	DrawBoard(&dc);
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Do nothing if it is O turn
	if (m_nNextChar != ex)
	{
		return;
	}

	// Do nothing if click occurred outside our window or if the square is non-empty
	int nPos = GetRectID(point);
	if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
	{
		return;
	}

	// Draw X and set turn to O
	m_nGameGrid[nPos] = ex;
	m_nNextChar = oh;

	CClientDC dc(this);
	DrawX(&dc, nPos);
	CheckForGameOver();
}

void CMainWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	// Do nothing if it is X turn
	if (m_nNextChar != oh)
	{
		return;
	}

	// Do nothing if click occurred outside our window or if the square is non-empty
	int nPos = GetRectID(point);
	if ((nPos == -1) || (m_nGameGrid[nPos] != 0))
	{
		return;
	}

	// Draw O and set turn to X
	m_nGameGrid[nPos] = oh;
	m_nNextChar = ex;

	CClientDC dc(this);
	DrawO(&dc, nPos);
	CheckForGameOver();
}

void CMainWindow::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// Reset the game if double left click occurred on the thick black lines that make up the grid
	CClientDC dc(this);
	if (dc.GetPixel(point) == RGB(0,0,0))
	{
		ResetGame();
	}
}

int CMainWindow::GetRectID(CPoint point)
{
	// Hit-test each of the grid's nine squares and return a rectangle ID (0-8) if (point.x, point.y) lies inside a square
	for (int i = 0; i < 9; i++)
	{
		if (m_rcSquares[i].PtInRect(point))
		{
			return i;
		}
	}
	return -1;
}

void CMainWindow::DrawBoard(CDC* pDC)
{
	// Draw the lines that define the tic-tac-toe grid
	CPen pen(PS_SOLID, 16, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(120, 16);
	pDC->LineTo(120, 336);

	pDC->MoveTo(232, 16);
	pDC->LineTo(232, 336);

	pDC->MoveTo(16, 120);
	pDC->LineTo(336, 120);

	pDC->MoveTo(16, 232);
	pDC->LineTo(336, 232);

	// Draw the Xs and Os

	for (int i = 0; i < 9; i++)
	{
		if (m_nGameGrid[i] == ex)
		{
			DrawX(pDC, i);
		}
		else if (m_nGameGrid[i] == oh)
		{
			DrawO(pDC, i);
		}
	}

	pDC->SelectObject(pOldPen);
}

void CMainWindow::DrawX(CDC* pDC, int nPos)
{
	CPen pen(PS_SOLID, 16, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	CRect rect = m_rcSquares[nPos];
	rect.DeflateRect(16, 16);
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->MoveTo(rect.left, rect.bottom);
	pDC->LineTo(rect.right, rect.top);

	pDC->SelectObject(pOldPen);
}

void CMainWindow::DrawO(CDC* pDC, int nPos)
{
	CPen pen(PS_SOLID, 16, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->SelectStockObject(NULL_BRUSH);

	CRect rect = m_rcSquares[nPos];
	rect.DeflateRect(16, 16);
	pDC->Ellipse(rect);

	pDC->SelectObject(pOldPen);
}

void CMainWindow::CheckForGameOver()
{
	int nWinner;

	// If the grid contains three consecutive Xs or Os declare a winner and start a new game
	if (nWinner = IsWinner())
	{
		CString string = (nWinner == ex) ? _T("X Wins!") : _T("O wins!");
		MessageBox(string, _T("Game Over"), MB_ICONEXCLAMATION | MB_OK);
		ResetGame();
	}
}

int CMainWindow::IsWinner()
{
	static int nPattern[8][3] =
	{
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		0, 3, 6,
		1, 4, 7,
		2, 5, 8,
		0, 4, 8,
		2, 4, 6
	};

	for (int i = 0; i < 8; i++)
	{
		if ((m_nGameGrid[nPattern[i][0]] == ex) && (m_nGameGrid[nPattern[i][1]] == ex) && (m_nGameGrid[nPattern[i][2]] == ex))
		{
			return ex;
		}

		if ((m_nGameGrid[nPattern[i][0]] == oh) && (m_nGameGrid[nPattern[i][1]] == oh) && (m_nGameGrid[nPattern[i][2]] == oh))
		{
			return oh;
		}
	}

	return 0;
}

BOOL CMainWindow::IsDraw()
{
	for (int i = 0; i < 9; i++)
	{
		if (m_nGameGrid[i] == 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}

void CMainWindow::ResetGame()
{
	m_nNextChar = ex;
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));
	Invalidate();
}