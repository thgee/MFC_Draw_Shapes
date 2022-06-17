
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

CChildView::CChildView() : onRect(true), onCircle(false), onCurve(false),
						   onStar(false), onSelect(false)
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
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DRAW_CIRCLE, &CChildView::OnDrawCircle)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CChildView::OnDrawRectangle)
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

	// ---------------------- Double Buffering------------------------
	CRect buffer_rect;
	GetClientRect(buffer_rect);
	int w = buffer_rect.Width();
	int h = buffer_rect.Height();

	CDC OffScrDC;
	OffScrDC.CreateCompatibleDC(&dc);
	CBitmap OffScrBmp;
	OffScrBmp.CreateCompatibleBitmap(&dc, w, h);
	OffScrDC.SelectObject(OffScrBmp);
	OffScrDC.Rectangle(0, 0, w, h);


	// ------------------------------- My Paint----------------------------------------
	CString str1;
	CString str2;
	str1.Format(_T("Number of Shapes : %d"), shapes.size());
	str2.Format(_T("Number of Selected : %d"), shapes.size());
	OffScrDC.TextOutW(5, 5, str1);
	OffScrDC.TextOutW(5, 25, str2);



	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw(&OffScrDC);
	}


	//---------------------------------------------------------------------------------

	dc.BitBlt(0, 0, w, h, &OffScrDC, 0, 0, SRCCOPY);
}

int dragging = 0;
//////////////////////// selecting은 shape 클래스 내에 넣을것
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	dragging = 1;
	
	if (onRect) {
		Rect* R = new Rect;
		R->c_pt = point;
		R->m_pt = point;

		shapes.push_back(R);
	}

	if (onCircle) {
		Circle* C = new Circle;
		C->c_pt = point;
		C->m_pt = point;
		
		shapes.push_back(C);
	}




	// Random Color Part
	int ran[3];
	for (int i = 0; i < 3; i++) ran[i] = rand() % 256; // 1 ~ 255 중에 랜덤으로 추출하여 RGB값으로 넣어줌
	shapes[shapes.size() - 1]->color = RGB(ran[0], ran[1], ran[2]);

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
	if (onRect && dragging == 1) { // 사각형 Draw모드
		Rect* R = (Rect*)shapes[shapes.size() - 1];
		R->m_pt = point;
	}

	if (onCircle && dragging == 1) { // 원 Draw모드
		Circle* C = (Circle*)shapes[shapes.size() - 1];
		C->m_pt = point;
	}

	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}



// Double Buffering
BOOL CChildView::OnEraseBkgnd(CDC* pDC){
	return true;
}



// 우클릭 시 메뉴 팝업
void CChildView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenuW(IDR_MAINFRAME);
	CMenu* pMenu = menu.GetSubMenu(3); // 메뉴중에 3 인덱스에 있는 메뉴를 가져옴
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
}


void CChildView::OnDrawCircle()
{
	onCircle = true;
	onRect = false;
}


void CChildView::OnDrawRectangle()
{
	onRect = true;
	onCircle = false;
}
