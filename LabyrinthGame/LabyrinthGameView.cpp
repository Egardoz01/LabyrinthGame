﻿
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


HBITMAP hBitmapMouse = NULL;

HBITMAP hBitmapCheese = NULL;


LRESULT CALLBACK DrawMouse(HDC hdc, UINT message, int Mouse_x, int Mouse_y, int Cheese_x, int Cheese_y)
{
	int result = 0;
	switch (message)
	{

	case WM_CREATE:
		hBitmapMouse = (HBITMAP)LoadImage(NULL, L"mouse.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitmapCheese = (HBITMAP)LoadImage(NULL, L"cheese.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
	case WM_PAINT:
		
		BITMAP          bitmap;
		HDC             hdcMem;
		HGDIOBJ         oldBitmap;
		
		


		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmapCheese);
		GetObject(hBitmapCheese, sizeof(bitmap), &bitmap);
		result = BitBlt(hdc, Cheese_x, Cheese_y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);


		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmapMouse);
		GetObject(hBitmapMouse, sizeof(bitmap), &bitmap);
		result = BitBlt(hdc, Mouse_x, Mouse_y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);

		break;
	
	
	}
	return 0;
}


void CLabyrinthGameView::DrawGrid(CDC* pDC)
{
	CLabyrinthGameDoc* doc = GetDocument();
	//for(int i = 0; i<pDoc->grid.)
	CPoint sPoint = CPoint(5, 5);
	int n = doc->grid._nRows;
	int m = doc->grid._nColumns;
	int height = doc->cellHeight;
	int width = doc->cellWidth;

	if (doc->firstDraw)
	{
		doc->firstDraw = false;


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

		DrawMouse(pDC->m_hDC, WM_CREATE, doc->Mouse_x, doc->Mouse_y, doc->Cheese_x, doc->Cheese_y);
	}



	DrawMouse(pDC->m_hDC, WM_PAINT, doc->Mouse_x, doc->Mouse_y, doc->Cheese_x, doc->Cheese_y);

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
			if (doc->grid.grid[i][j].top)
			{
				pDC->MoveTo(curX, curY);
				pDC->LineTo(curX + width, curY);

			}

			if (doc->grid.grid[i][j].right)
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
	CLabyrinthGameDoc* doc = GetDocument();

	switch (nChar)
	{
	case VK_LEFT:	// стрелка влево
		if (doc->MouceCell_x > 0)
		{
			if (doc->grid.grid[doc->MouceCell_y][doc->MouceCell_x - 1].right == false)
			{
				doc->MouceCell_x--;
				doc->Mouse_x -= doc->cellWidth;
			}
		}
		break;
	case VK_RIGHT:	// стрелка вправо
		if (doc->MouceCell_x < doc->grid._nColumns-1)
		{
			if (doc->grid.grid[doc->MouceCell_y][doc->MouceCell_x].right == false)
			{
				doc->MouceCell_x++;
				doc->Mouse_x += doc->cellWidth;
			}
		}
		break;
	case VK_UP:		// стрелка вверх
		if (doc->MouceCell_y > 0)
		{
			if (doc->grid.grid[doc->MouceCell_y][doc->MouceCell_x].top == false)
			{
				doc->MouceCell_y--;
				doc->Mouse_y -= doc->cellHeight;
			}
		}
		break;
	case VK_DOWN:		// стрелка вверх
		if (doc->MouceCell_y < doc->grid._nRows - 1)
		{
			if (doc->grid.grid[doc->MouceCell_y+1][doc->MouceCell_x].top == false)
			{
				doc->MouceCell_y++;
				doc->Mouse_y += doc->cellHeight;
			}
		}
		break;
	}

	this->RedrawWindow();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
