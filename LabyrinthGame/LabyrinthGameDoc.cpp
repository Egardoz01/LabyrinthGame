
// LabyrinthGameDoc.cpp : implementation of the CLabyrinthGameDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LabyrinthGame.h"
#endif

#include "LabyrinthGameDoc.h"

#include <propkey.h>

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/
// CLabyrinthGameDoc

IMPLEMENT_DYNCREATE(CLabyrinthGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CLabyrinthGameDoc, CDocument)
END_MESSAGE_MAP()


// CLabyrinthGameDoc construction/destruction

CLabyrinthGameDoc::CLabyrinthGameDoc() noexcept
{
	this->grid = Grid(5,5);
	cellHeight = 35;
	cellWidth = 35;
	Mouse_x = 10;
	Mouse_y = 10;
	MouceCell_x = 0;
	MouceCell_y = 0;
	firstDraw = true;
	Cheese_x = 10 + cellWidth * (grid._nColumns-1);
	Cheese_y = 10 + cellHeight * (grid._nRows-1);
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
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
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
