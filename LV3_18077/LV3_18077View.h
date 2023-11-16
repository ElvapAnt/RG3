
// LV3_18077View.h : interface of the CLV318077View class
//

#include "DImage.h"
#pragma once


class CLV318077View : public CView
{
protected: // create from serialization only
	CLV318077View() noexcept;
	DECLARE_DYNCREATE(CLV318077View)

// Attributes
public:
	CLV318077Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLV318077View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DImage m_puzzlePiece1;
	DImage m_puzzlePiece2;
	DImage m_puzzlePiece3;
	DImage m_puzzlePiece4;
	DImage m_puzzlePiece5;
	DImage m_puzzlePiece6;
	DImage m_puzzlePiece7;
	DImage m_puzzlePiece8;
	DImage m_puzzlePiece9;
	CBitmap* TransparentMask(CDC* pDC, CBitmap* image, int width, int height);
	void DrawPuzzlePiece(CDC* pDC, DImage& img, const CPoint& position, float angle, float scaleX, float scaleY, bool mirrorX, bool mirrorY, bool isBlue = false);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply);
	void GrayscaleFilter(CBitmap* pBitmap,bool isBlue);
	void DrawGrid(CDC* pDC);
	void DrawPuzzle(CDC* pDC);
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LV3_18077View.cpp
inline CLV318077Doc* CLV318077View::GetDocument() const
   { return reinterpret_cast<CLV318077Doc*>(m_pDocument); }
#endif

