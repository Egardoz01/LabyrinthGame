
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
private:
	int mouse_x;
	int mouse_y;
	int cheese_x;
	int cheese_y;

	int cellHeight;
	int cellWidth;
	HBITMAP hBitmapMouse;
	HBITMAP hBitmapCheese;
	CPoint sPoint;
	UINT_PTR mainTimer;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void KillMainTimer();
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
	void DrawMouse(HDC hdc);
	void ResizeWindow();

public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in LabyrinthGameView.cpp
inline CLabyrinthGameDoc* CLabyrinthGameView::GetDocument() const
   { return reinterpret_cast<CLabyrinthGameDoc*>(m_pDocument); }
#endif

