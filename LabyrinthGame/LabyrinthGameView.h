
// LabyrinthGameView.h : interface of the CLabyrinthGameView class
//

#pragma once


class CLabyrinthGameView : public CView
{
protected: // create from serialization only
	CLabyrinthGameView() noexcept;
	DECLARE_DYNCREATE(CLabyrinthGameView)

// Attributes
public:
	CLabyrinthGameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CLabyrinthGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()


private:
	void DrawGrid(CDC* pDC);
};

#ifndef _DEBUG  // debug version in LabyrinthGameView.cpp
inline CLabyrinthGameDoc* CLabyrinthGameView::GetDocument() const
   { return reinterpret_cast<CLabyrinthGameDoc*>(m_pDocument); }
#endif

