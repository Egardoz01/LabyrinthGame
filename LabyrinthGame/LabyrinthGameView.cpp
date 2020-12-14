
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
	CPoint sPoint = CPoint(-pDoc->cellWidth+5,5);
	int n = pDoc->grid._nRows;
	int m = pDoc->grid._nColumns;
	for (int i = 0; i < n; i++)
	{
		int curY = sPoint.y+i*pDoc->cellHeight;
		int curX = sPoint.x;
		for (int j = 0; j < m; j++)
		{
			if (pDoc->grid.grid[i][j].top)
			{
				pDC->MoveTo(curX, curY);
				pDC->LineTo(curX+ pDoc->cellWidth,curY);

			}

			if (pDoc->grid.grid[i][j].right)
			{
				pDC->MoveTo(curX+ pDoc->cellWidth, curY);
				pDC->LineTo(curX + pDoc->cellWidth, curY + pDoc->cellHeight);

			}

			curX += pDoc->cellWidth;
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


