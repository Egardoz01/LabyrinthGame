
// LabyrinthGameDoc.cpp : implementation of the CLabyrinthGameDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LabyrinthGame.h"
#endif

#include "LabyrinthGameDoc.h"
#include "LabyrinthGameView.h"
#include <propkey.h>
#include "CongratDialog.h"
#include "StartGameForm.h"
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/
// CLabyrinthGameDoc



IMPLEMENT_DYNCREATE(CLabyrinthGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CLabyrinthGameDoc, CDocument)
//	ON_COMMAND(ID_NEW_GAME, &CLabyrinthGameDoc::OnNewGame)
//ON_COMMAND(ID_NEW_GAME, &CLabyrinthGameDoc::OnNewGame)
END_MESSAGE_MAP()


// CLabyrinthGameDoc construction/destruction

CLabyrinthGameDoc::CLabyrinthGameDoc() noexcept
{

	GameStarted = false;
	LoadSave = false;

}

void CLabyrinthGameDoc::StartGame()
{

	StartGameForm frm;
	frm.DoModal();

	if (!frm.DialogResult)
		return;

	GameStarted = true;
	int nRows;
	int nColumns;
	switch (frm.Level2)
	{
	case EASY:
		nRows = 5;
		nColumns = 5;
		break;
	case MEDIUM:
		nRows = 20;
		nColumns = 20;
		break;
	case HARD:
		nRows = 20;
		nColumns = 40;
		break;

	}
	LGrid.Initialize(nRows, nColumns);

	MouceCell_x = 0;
	MouceCell_y = 0;
	CheeseCell_x = LGrid.nColumns - 1;
	CheeseCell_y = LGrid.nRows - 1;

	CurSeconds = 0;
	
}

void CLabyrinthGameDoc::DoCongratulations(CString text)
{
	CongratDialog dlg;
	dlg.strCongrText = text;
	dlg.DoModal();
}

void CLabyrinthGameDoc::CheckForGameFinish()
{
	if (MouceCell_x == CheeseCell_x && MouceCell_y == CheeseCell_y)
	{
		FinishGame();
	}
}

void CLabyrinthGameDoc::FinishGame()
{
	GameStarted = false;
	CLabyrinthGameView * curView = NULL;
	POSITION pos = GetFirstViewPosition();
	if (pos != NULL)
	{
		curView = (CLabyrinthGameView*)GetNextView(pos);
		curView->FinishGame();
	}
	CString strCongratulations;
	strCongratulations.Format(_T("CONGRATULATIONS!!! IT TOOK %d sec to pass the labyrinth"), CurSeconds);

	DoCongratulations(strCongratulations);

}

/*
void CLabyrinthGameView* CLabyrinthGameDoc::GetView()
{
	CLabyrinthGameView * curView = NULL;
	POSITION pos = GetFirstViewPosition();
	if (pos != NULL)
		curView = (CLabyrinthGameView*)GetNextView(pos);

	return curView;
}*/

void CLabyrinthGameDoc::RightStep()
{
	if (MouceCell_x < LGrid.nColumns - 1)
	{
		if (LGrid.grid[MouceCell_y][MouceCell_x].right == false)
		{
			MouceCell_x++;
		}
	}
}

void CLabyrinthGameDoc::LeftStep()
{
	if (MouceCell_x > 0)
	{
		if (LGrid.grid[MouceCell_y][MouceCell_x - 1].right == false)
		{
			MouceCell_x--;
		}
	}
}

void CLabyrinthGameDoc::UpStep()
{
	if (MouceCell_y > 0)
	{
		if (LGrid.grid[MouceCell_y][MouceCell_x].top == false)
		{
			MouceCell_y--;
		}
	}
}

void CLabyrinthGameDoc::DownStep()
{
	if (MouceCell_y < LGrid.nRows - 1)
	{
		if (LGrid.grid[MouceCell_y + 1][MouceCell_x].top == false)
		{
			MouceCell_y++;
		}
	}
}

CLabyrinthGameDoc::~CLabyrinthGameDoc()
{

}

BOOL CLabyrinthGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}





// CLabyrinthGameDoc serialization

void CLabyrinthGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << MouceCell_x << MouceCell_y << CheeseCell_x << CheeseCell_y << CurSeconds;
	}
	else
	{
		ar >> MouceCell_x >> MouceCell_y >> CheeseCell_x >> CheeseCell_y >> CurSeconds;
		LoadSave = true;
		StartGame();
	}

	LGrid.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CLabyrinthGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CLabyrinthGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CLabyrinthGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CLabyrinthGameDoc diagnostics

#ifdef _DEBUG
void CLabyrinthGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLabyrinthGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLabyrinthGameDoc commands


