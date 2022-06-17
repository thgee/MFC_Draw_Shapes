
// ChildView.cpp: CChildView 클래스의 구현
//


#include "pch.h"
#include "framework.h"
#include "Draw_Shapes.h"
#include "ChildView.h"
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	CRect rect;
	GetClientRect(rect);
	int w = rect.Width();
	int h = rect.Height();

	CDC OffScrDC;
	OffScrDC.CreateCompatibleDC(&dc);
	CBitmap OffScrBmp;
	OffScrBmp.CreateCompatibleBitmap(&dc, w, h);
	OffScrDC.SelectObject(OffScrBmp);
	OffScrDC.Rectangle(0, 0, w, h);



	CString str;
	str.Format(_T("현재 도형의 수 : %d"), shapes.size());
	OffScrDC.TextOutW(0, 0, str);

	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw(&OffScrDC);
	}


	dc.BitBlt(0, 0, w, h, &OffScrDC, 0, 0, SRCCOPY);

}

int dragging = 0;
//////////////////////// selecting은 shape 클래스 내에 넣을것
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	dragging = 1;
	Circle* C = new Circle;
	C->c_pt = point;
	C->m_pt = point;
	int ran[3];
	for (int i = 0; i < 3; i++) ran[i] = rand() % 256;
	C->color = RGB(ran[0], ran[1], ran[2]); // 랜덤하게 색이 변화함
	shapes.push_back(C);
	

	SetCapture();
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	dragging = 0;

	Invalidate();
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (dragging == 1) {
		Circle* C = (Circle*)shapes[shapes.size() - 1];
		C->m_pt = point;

		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
		
	return true;
}
