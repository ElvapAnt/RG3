
// LV3_18077View.cpp : implementation of the CLV318077View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV3_18077.h"
#endif

#include "LV3_18077Doc.h"
#include "LV3_18077View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vector>


// CLV318077View

IMPLEMENT_DYNCREATE(CLV318077View, CView)

BEGIN_MESSAGE_MAP(CLV318077View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLV318077View construction/destruction

CLV318077View::CLV318077View() noexcept
{
	// TODO: add construction code here
	m_puzzlePiece1.Load(CString("./res/pz1.bmp"));
	m_puzzlePiece2.Load(CString("./res/pz2.bmp"));
	m_puzzlePiece3.Load(CString("./res/pz3.bmp"));
	m_puzzlePiece4.Load(CString("./res/pz4.bmp"));
	m_puzzlePiece5.Load(CString("./res/pz5.bmp"));
	m_puzzlePiece6.Load(CString("./res/pz6.bmp"));
	m_puzzlePiece7.Load(CString("./res/pz7.bmp"));
	m_puzzlePiece8.Load(CString("./res/pz8.bmp"));
	m_puzzlePiece9.Load(CString("./res/pz9.bmp"));

}

CLV318077View::~CLV318077View()
{
}

BOOL CLV318077View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLV318077View drawing

void CLV318077View::OnDraw(CDC* pDC)
{
	CLV318077Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DrawPuzzle(pDC);
}


// CLV318077View printing

BOOL CLV318077View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLV318077View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLV318077View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLV318077View diagnostics

#ifdef _DEBUG
void CLV318077View::AssertValid() const
{
	CView::AssertValid();
}

void CLV318077View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitmap* CLV318077View::TransparentMask(CDC* pDC, CBitmap* image, int width, int height)
{
	CBitmap* bmpMask = new CBitmap();
	bmpMask->CreateBitmap(width, height, 1, 1, NULL);
	CDC SrcDC;
	SrcDC.CreateCompatibleDC(pDC);
	CDC DstDC;
	DstDC.CreateCompatibleDC(pDC);
	CBitmap* pOldSrcBmp = SrcDC.SelectObject(image);
	CBitmap* pOldDstBmp = DstDC.SelectObject(bmpMask);

	COLORREF clrTopLeft = SrcDC.GetPixel(0, 0);
	COLORREF clrSaveBk = SrcDC.SetBkColor(clrTopLeft);
	DstDC.BitBlt(0, 0, width, height, &SrcDC, 0, 0, SRCCOPY);
	COLORREF clrSaveDstText = SrcDC.SetTextColor(RGB(255, 255, 255));
	SrcDC.SetBkColor(RGB(0, 0, 0));
	SrcDC.BitBlt(0, 0, width, height, &DstDC, 0, 0, SRCAND);

	DstDC.SetTextColor(clrSaveDstText);
	SrcDC.SetBkColor(clrSaveBk);
	SrcDC.SelectObject(pOldSrcBmp);
	DstDC.SelectObject(pOldDstBmp);

	SrcDC.DeleteDC();
	DstDC.DeleteDC();

	return bmpMask;
}
void CLV318077View::DrawPuzzlePiece(CDC* pDC, DImage& img, const CPoint& position, float angle, float scaleX, float scaleY, bool mirrorX, bool mirrorY, bool isBlue)
{

	int width = img.Width();
	int height = img.Height();
	int savedDC = pDC->SaveDC();
	pDC->SetGraphicsMode(GM_ADVANCED);

	Translate(pDC, position.x, position.y, false);
	Mirror(pDC, mirrorX, mirrorY, false);
	Rotate(pDC, angle, false);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmpImg;
	bmpImg.CreateCompatibleBitmap(pDC, img.Width(), img.Height());
	CBitmap* pOldBmp = memDC.SelectObject(&bmpImg);
	img.Draw(&memDC, CRect(0, 0, img.Width(), img.Height()), CRect(0, 0, img.Width(), img.Height()));
	memDC.SelectObject(pOldBmp);
	//CBitmap *bmpImg = img.GetBitmap();
	GrayscaleFilter(&bmpImg, isBlue);
	CBitmap* mask = TransparentMask(pDC, &bmpImg, width, height);

	pOldBmp = memDC.SelectObject(mask);
	pDC->BitBlt(-width/2 + 3, -height/2 - 10, width, height, &memDC, 0, 0, SRCAND);

	memDC.SelectObject(&bmpImg);
	pDC->BitBlt(-width / 2 + 3, -height / 2 - 10, width, height, &memDC, 0, 0, SRCPAINT);

	memDC.SelectObject(pOldBmp);
	delete mask; 

	pDC->RestoreDC(savedDC);
}
void CLV318077View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xForm = { 1, 0, 0, 1, dX, dY };
	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CLV318077View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM xForm = { sX, 0, 0, sY, 0, 0 };
	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CLV318077View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	float rad = angle * 3.14159265f / 180.0f;
	XFORM xForm = { cos(rad), sin(rad), -sin(rad), cos(rad), 0, 0 };
	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CLV318077View::Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply)
{
	XFORM xForm = { mx ? -1.0f : 1.0f, 0, 0, my ? -1.0f : 1.0f, 0, 0 };
	pDC->ModifyWorldTransform(&xForm, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CLV318077View::GrayscaleFilter(CBitmap* pBitmap, bool isBlue)
{
	BITMAP b;
	pBitmap->GetBitmap(&b);
	u_char* bits = new u_char[b.bmWidthBytes * b.bmHeight];
	pBitmap->GetBitmapBits(b.bmWidthBytes * b.bmHeight, bits);
	for (int i = 0; i < b.bmWidthBytes * b.bmHeight; i += 4)
	{
		if (bits[i + 1] == 255)
			continue;
		u_char newPixel = 64 + (bits[i] + bits[i + 1] + bits[i + 2]) / 3;
		newPixel = newPixel > 255 ? 255 : newPixel;
		bits[i] = isBlue ? bits[i] : newPixel;
		bits[i + 1] = isBlue ? 0 : newPixel;
		bits[i + 2] = isBlue ? 0 : newPixel;
	}
	pBitmap->SetBitmapBits(b.bmWidthBytes * b.bmHeight, bits);
	delete[] bits;
}
void CLV318077View::DrawGrid(CDC* pDC)
{
	CPen pen(PS_SOLID, 2, RGB(128, 128, 128));
	CPen* oldPen = pDC->SelectObject(&pen);
	const int gridSize = 25;
	const int width = 500;
	const int height = 500;

	for (int x = 0; x <= width; x += gridSize)
	{
		pDC->MoveTo(x, 0);
		pDC->LineTo(x, height);
	}

	for (int y = 0; y <= height; y += gridSize)
	{
		pDC->MoveTo(0, y);
		pDC->LineTo(width, y);
	}

	pDC->SelectObject(oldPen);
}
void CLV318077View::DrawPuzzle(CDC* pDC)
{
	CDC* memDC = new CDC();
	(*memDC).CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, 500, 500);
	CBitmap* pOldBitmap = (*memDC).SelectObject(&bitmap);
	CBrush bgBrush(RGB(255, 255, 255)); 
	CRect rc(0, 0, 500, 500);
	(*memDC).FillRect(rc, &bgBrush);
	DrawGrid(memDC);

	int savedDC = pDC->SaveDC();
	pDC->SetGraphicsMode(GM_ADVANCED);
	Translate(pDC, -250, -250, true);
	Rotate(pDC, 180, true);
	Translate(pDC, 250, 250, true);
	
	DrawPuzzlePiece(memDC, m_puzzlePiece1, CPoint(100, 100), -202, 1, 1, true, false);
	DrawPuzzlePiece(memDC, m_puzzlePiece7, CPoint(250, 100), -57, 1, 1, true, false);
	DrawPuzzlePiece(memDC, m_puzzlePiece5, CPoint(400, 100), -228, 1, 1, true, false);

	DrawPuzzlePiece(memDC, m_puzzlePiece9, CPoint(100, 250), -70, 1, 1, true, false);
	DrawPuzzlePiece(memDC, m_puzzlePiece2, CPoint(250, 250), -40, 1, 1, true, false);
	DrawPuzzlePiece(memDC, m_puzzlePiece3, CPoint(400, 250), -25, 1, 1, true, false);

	DrawPuzzlePiece(memDC, m_puzzlePiece4, CPoint(100, 400), -95, 1, 1, true, false);
	DrawPuzzlePiece(memDC, m_puzzlePiece6, CPoint(250, 400), 156, 1, 1, true, false, true);
	DrawPuzzlePiece(memDC, m_puzzlePiece8, CPoint(400, 400), 200, 1, 1, true, false);

	pDC->BitBlt(0, 0, 500, 500, memDC, 0, 0, SRCCOPY);

	pDC->RestoreDC(savedDC);
	(*memDC).SelectObject(pOldBitmap);
	bitmap.DeleteObject();
}

CLV318077Doc* CLV318077View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLV318077Doc)));
	return (CLV318077Doc*)m_pDocument;
}
#endif //_DEBUG


// CLV318077View message handlers
