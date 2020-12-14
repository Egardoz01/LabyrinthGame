
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

void CLabyrinthGameView::DrawGrid(CDC* pDC)
{
	CLabyrinthGameDoc* pDoc = GetDocument();
	//for(int i = 0; i<pDoc->grid.)
	CPoint sPoint = CPoint(5,5);
	int n = pDoc->grid._nRows;
	int m = pDoc->grid._nColumns;
	int height = pDoc->cellHeight;
	int width = pDoc->cellWidth;

	pDC->MoveTo(sPoint);
	pDC->LineTo(sPoint.x, sPoint.y+n*height);
	pDC->MoveTo(sPoint.x, sPoint.y + n * height);
	pDC->LineTo(sPoint.x + m*width, sPoint.y + n * height);//рисуем границы

	for (int i = 0; i < n; i++)
	{
		int curY = sPoint.y+i* height;
		int curX = sPoint.x;
		for (int j = 0; j < m; j++)
		{
			if (pDoc->grid.grid[i][j].top)
			{
				pDC->MoveTo(curX, curY);
				pDC->LineTo(curX+ width,curY);

			}

			if (pDoc->grid.grid[i][j].right)
			{
				pDC->MoveTo(curX+ width, curY);
				pDC->LineTo(curX + width, curY + height);

			}

			curX += width;
		}
	}
	
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
			height * n + nHeightDiff+ 10;
		//  The MoveWindow function resizes the frame window
		GetParentFrame()->MoveWindow(&rcWindow);
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


