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
	ON_WM_TIMER()
	ON_COMMAND(ID_NEW_GAME, &CLabyrinthGameView::OnNewGame)
END_MESSAGE_MAP()



// CLabyrinthGameView construction/destruction

CLabyrinthGameView::CLabyrinthGameView() noexcept
{

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
	CLabyrinthGameDoc* doc = GetDocument();
	ASSERT_VALID(doc);
	if (!doc)
		return;

	if (doc->GameStarted)
	{
		DrawMouse(pDC->m_hDC);
		DrawGrid(pDC);
	}
}





void CLabyrinthGameView::DrawMouse(HDC hdc)
{

	CLabyrinthGameDoc* doc = GetDocument();

	BITMAP          bitmap;
	HDC             hdcMem;
	HGDIOBJ         oldBitmap;


	cheese_x = sPoint.x + 5 + cellWidth * doc->CheeseCell_x;
	cheese_y = sPoint.y + 5 + cellHeight * doc->CheeseCell_y;



	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hBitmapCheese);
	GetObject(hBitmapCheese, sizeof(bitmap), &bitmap);
	BitBlt(hdc, cheese_x, cheese_y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);


	mouse_x = sPoint.x + 5 + doc->MouceCell_x*cellWidth;
	mouse_y = sPoint.y + 5 + doc->MouceCell_y*cellHeight;

	hdcMem = CreateCompatibleDC(hdc);
	oldBitmap = SelectObject(hdcMem, hBitmapMouse);
	GetObject(hBitmapMouse, sizeof(bitmap), &bitmap);
	BitBlt(hdc, mouse_x, mouse_y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, oldBitmap);
	DeleteDC(hdcMem);

}


void CLabyrinthGameView::DrawGrid(CDC* pDC)
{
	CLabyrinthGameDoc* doc = GetDocument();
	//for(int i = 0; i<pDoc->grid.)
	
	int n = doc->LGrid.nRows;
	int m = doc->LGrid.nColumns;
	int height = cellHeight;
	int width = cellWidth;

	pDC->MoveTo(sPoint);
	pDC->LineTo(sPoint.x, sPoint.y + n * height);
	pDC->MoveTo(sPoint.x, sPoint.y + n * height);
	pDC->LineTo(sPoint.x + m * width, sPoint.y + n * height);//рисуем границы
	RECT rect;
	rect.left = 5;
	rect.top = 5;
	CString strTime;
	strTime.Format(_T("Текущее время %d%d:%d%d"), ((doc->CurSeconds / 600) % 10), ((doc->CurSeconds / 60) % 10), ((doc->CurSeconds / 10)%6), (doc->CurSeconds % 10));

	pDC->DrawText(strTime, &rect, DT_SINGLELINE | DT_NOCLIP);

	for (int i = 0; i < n; i++)
	{
		int curY = sPoint.y + i * height;
		int curX = sPoint.x;
		for (int j = 0; j < m; j++)
		{
			if (doc->LGrid.grid[i][j].top)
			{
				pDC->MoveTo(curX, curY);
				pDC->LineTo(curX + width, curY);

			}

			if (doc->LGrid.grid[i][j].right)
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
		doc->LeftStep();
		break;
	case VK_RIGHT:	// стрелка вправо
		doc->RightStep();
		break;
	case VK_UP:		// стрелка вверх
		doc->UpStep();
		break;
	case VK_DOWN:		// стрелка вверх
		doc->DownStep();
		break;
	}

	this->RedrawWindow();
	doc->CheckForGameFinish();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CLabyrinthGameView::ResizeWindow()
{

	CLabyrinthGameDoc* doc = GetDocument();

	ASSERT_VALID(doc);
	if (!doc)
		return;
	

	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
		
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	
	rcWindow.right = rcWindow.left +
		cellWidth * doc->LGrid.nColumns + nWidthDiff + sPoint.x+5;
	rcWindow.bottom = rcWindow.top +
		cellHeight * doc->LGrid.nRows + nHeightDiff + sPoint.y + 5;

	GetParentFrame()->MoveWindow(&rcWindow);


	
}



void CLabyrinthGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	
}


void CLabyrinthGameView::OnTimer(UINT_PTR nIDEvent)
{
	GetDocument()->CurSeconds++;
	this->RedrawWindow();

	CView::OnTimer(nIDEvent);
}

void CLabyrinthGameView::FinishGame()
{
	KillTimer(mainTimer);
	RedrawWindow();
}

void CLabyrinthGameView::StartGame()
{
	cellHeight = 35;
	cellWidth = 35;
	sPoint = CPoint(5, 50);



	hBitmapMouse = (HBITMAP)LoadImage(NULL, L"mouse.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmapCheese = (HBITMAP)LoadImage(NULL, L"cheese.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	ResizeWindow();


	mainTimer = SetTimer(1, 1000, NULL);

}


void CLabyrinthGameView::OnNewGame()
{
	GetDocument()->StartGame();
	StartGame();
}
