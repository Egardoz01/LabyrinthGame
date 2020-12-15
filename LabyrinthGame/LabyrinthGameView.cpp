
// LabyrinthGameView.cpp : implementation of the CLabyrinthGameView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LabyrinthGame.h"
#endif

#include "LabyrinthGameDoc.h"
#include "LabyrinthGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLabyrinthGameView

IMPLEMENT_DYNCREATE(CLabyrinthGameView, CView)

BEGIN_MESSAGE_MAP(CLabyrinthGameView, CView)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CLabyrinthGameView construction/destruction

CLabyrinthGameView::CLabyrinthGameView() noexcept
{
	// TODO: add construction code here

}

CLabyrinthGameView::~CLabyrinthGameView()
{
}

BOOL CLabyrinthGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
	
}

// CLabyrinthGameView drawing

void CLabyrinthGameView::OnDraw(CDC* pDC)
{
	CLabyrinthGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawGrid(pDC);
}


HBITMAP hBitmap = NULL;

int x_mouse=10, y_mouse=10;

LRESULT CALLBACK DrawMouse(HDC hdc, UINT message)
{
	int result = 0;
	switch (message)
	{

	case WM_CREATE:
		hBitmap = (HBITMAP)LoadImage(NULL, L"mouse.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
	case WM_PAINT:
		PAINTSTRUCT     ps;
		
		BITMAP          bitmap;
		HDC             hdcMem;
		HGDIOBJ         oldBitmap;
		
		//hdc = BeginPaint(hWnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap);

		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		result = BitBlt(hdc, x_mouse, y_mouse, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
	
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);

		//EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	
	}
	return 0;
}


void CLabyrinthGameView::DrawGrid(CDC* pDC)
{
	CLabyrinthGameDoc* pDoc = GetDocument();
	//for(int i = 0; i<pDoc->grid.)
	CPoint sPoint = CPoint(5, 5);
	int n = pDoc->grid._nRows;
	int m = pDoc->grid._nColumns;
	int height = pDoc->cellHeight;
	int width = pDoc->cellWidth;

	if (pDoc->firstDraw)
	{
		pDoc->firstDraw = false;


		CRect rcClient, rcWindow;
		GetClientRect(&rcClient);
		GetParentFrame()->GetWindowRect(&rcWindow);
		//  Calculate the difference
		int nWidthDiff = rcWindow.Width() - rcClient.Width();
		int nHeightDiff = rcWindow.Height() - rcClient.Height();
		//  Change the window size based on the size of the game board
		rcWindow.right = rcWindow.left +
			width * m + nWidthDiff + 10;
		rcWindow.bottom = rcWindow.top +
			height * n + nHeightDiff + 10;
		//  The MoveWindow function resizes the frame window
		GetParentFrame()->MoveWindow(&rcWindow);

		DrawMouse(pDC->m_hDC, WM_CREATE);
	}



	DrawMouse(pDC->m_hDC, WM_PAINT);

	pDC->MoveTo(sPoint);
	pDC->LineTo(sPoint.x, sPoint.y + n * height);
	pDC->MoveTo(sPoint.x, sPoint.y + n * height);
	pDC->LineTo(sPoint.x + m * width, sPoint.y + n * height);//рисуем границы

	for (int i = 0; i < n; i++)
	{
		int curY = sPoint.y + i * height;
		int curX = sPoint.x;
		for (int j = 0; j < m; j++)
		{
			if (pDoc->grid.grid[i][j].top)
			{
				pDC->MoveTo(curX, curY);
				pDC->LineTo(curX + width, curY);

			}

			if (pDoc->grid.grid[i][j].right)
			{
				pDC->MoveTo(curX + width, curY);
				pDC->LineTo(curX + width, curY + height);

			}

			curX += width;
		}
	}

	


	

}


// CLabyrinthGameView diagnostics

#ifdef _DEBUG
void CLabyrinthGameView::AssertValid() const
{
	CView::AssertValid();
}

void CLabyrinthGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLabyrinthGameDoc* CLabyrinthGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLabyrinthGameDoc)));
	return (CLabyrinthGameDoc*)m_pDocument;
}
#endif //_DEBUG




void CLabyrinthGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	switch (nChar)
	{
	case VK_LEFT:	// стрелка влево
		x_mouse -= 35;
		break;
	case VK_RIGHT:	// стрелка вправо
	
		x_mouse += 35;
		break;
	case VK_UP:		// стрелка вверх
		y_mouse -= 35;
		break;
	case VK_DOWN:		// стрелка вверх
		y_mouse += 35;
		break;
	}

	this->RedrawWindow();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
