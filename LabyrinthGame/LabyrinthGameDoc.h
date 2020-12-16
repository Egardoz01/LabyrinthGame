
// LabyrinthGameDoc.h : interface of the CLabyrinthGameDoc class
//
#include "Grid.h"

#pragma once


class CLabyrinthGameDoc : public CDocument
{
protected: // create from serialization only
	CLabyrinthGameDoc() noexcept;
	DECLARE_DYNCREATE(CLabyrinthGameDoc)

// Attributes
public:
	Grid LGrid;
	int MouceCell_x;
	int MouceCell_y;
	int CheeseCell_x;
	int CheeseCell_y;
	int CurSeconds;
	
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	void DoCongratulations(CString text);
	void FinishGame();
	void RightStep();
	void LeftStep();
	void UpStep();
	void DownStep();
	virtual ~CLabyrinthGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
