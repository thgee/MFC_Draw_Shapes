
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

// degree 를 radian으로 변환하는 함수
float CChildView:: DegToRad(float deg) {
	return (deg * 3.141592 / 180.0f);
}

// Random Color function
void CChildView :: SetColor() {
	int ran[3];
	for (int i = 0; i < 3; i++) ran[i] = rand() % 256; // 1 ~ 255 중에 랜덤으로 추출하여 RGB값으로 넣어줌
	shapes[shapes.size() - 1]->color = RGB(ran[0], ran[1], ran[2]);
}

// 선택된 도형의 수를 받아오는 함수
int CChildView:: getSelectNum() {
	int cnt = 0;
	
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i]->selecting == true) cnt++;
	}
	return cnt;
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
	ON_COMMAND(ID_DRAW_CURVE, &CChildView::OnDrawCurve)
	ON_COMMAND(ID_DRAW_STAR, &CChildView::OnDrawStar)
	ON_COMMAND(ID_ACTION_SELECT, &CChildView::OnActionSelect)
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
	str2.Format(_T("Number of Selected : %d"), getSelectNum());
	OffScrDC.TextOutW(5, 5, str1);
	OffScrDC.TextOutW(5, 25, str2);



	for (int i = 0; i < shapes.size(); i++) {
		shapes[i]->draw(&OffScrDC);

		if (shapes[i]->selecting) 
			shapes[i]->drawRect(&OffScrDC);
	}




	//---------------------------------------------------------------------------------

	dc.BitBlt(0, 0, w, h, &OffScrDC, 0, 0, SRCCOPY);
}

int dragging = 0;
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	if (onRect) {
		dragging = 1;

		Rect* R = new Rect;
		R->c_pt = R->m_pt = point;

		shapes.push_back(R);
		SetColor();
	}

	if (onCircle) {
		dragging = 1;

		Circle* C = new Circle;
		C->c_pt = C->m_pt = point;
		
		shapes.push_back(C);
		SetColor();

	}

	if (onCurve) {
		dragging = 1;

		Line* L = new Line;
		L->pt1.push_back(point);

		shapes.push_back(L);
		SetColor();

	}

	if (onStar) {
		dragging = 1;

		Star* S = new Star;
		S->c_pt = point;

		shapes.push_back(S);
		SetColor();

	}
	if (onSelect) {
		for (int i = 0; i < shapes.size(); i++) {
			shapes[i]->selecting = false;


			if (shapes.size() >= 1 && shapes[i]->inPos(point)) { // 도형을 클릭하면
				dragging = 1;
				shapes[i]->selecting = true; // 클릭된 도형의 selecting이 true로 변함
				pre_pt = point; // 움직이기 전 좌표를 저장
			}
		}
	}

	


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
		Invalidate();

	}

	if (onCircle && dragging == 1) { // 원 Draw모드
		Circle* C = (Circle*)shapes[shapes.size() - 1];
		C->m_pt = point;
		Invalidate();

	}

	if (onCurve && dragging == 1) { // 곡선 Draw모드
		Line* L = (Line*)shapes[shapes.size() - 1];
		L->pt2.push_back(point);
		L->pt1.push_back(point);
		Invalidate();
	}

	if (onStar && dragging == 1) { // 별 Draw모드
		Star* S = (Star*)shapes[shapes.size() - 1];
		S->m_pt = point;
		S->long_dist = sqrt((S->m_pt.x - S->c_pt.x) * (S->m_pt.x - S->c_pt.x) +
							(S->m_pt.y - S->c_pt.y) * (S->m_pt.y - S->c_pt.y));
		S->short_dist = S->long_dist / 2.5f; // 짧은 꼭짓점 까지의 거리 계산

		

		// 긴 꼭짓점 좌표설정
		for (int i = 0; i <= 8; i = i + 2) {
			S->vtx[i].x = S->c_pt.x + S->long_dist * cos(DegToRad(-1 * ( - 18 + 36 * (i + 1)))); // -18도를 더해줌으로써 별의 모양을 정렬함
			S->vtx[i].y = S->c_pt.y + S->long_dist * sin(DegToRad(-1 * ( - 18 + 36 * (i + 1))));
		}

		// 짧은 꼭짓점 좌표설정
		for (int i = 1; i <= 9; i = i + 2) {
			S->vtx[i].x = S->c_pt.x + S->short_dist * cos(DegToRad(-1 * ( - 18 + 36 * (i + 1))));
			S->vtx[i].y = S->c_pt.y + S->short_dist * sin(DegToRad(-1 * ( - 18 + 36 * (i + 1))));
		}

		Invalidate();
	}
	
	if (onSelect && dragging == 1)
		for (int i = 0; i < shapes.size(); i++) {
			if (shapes[i]->selecting) {
				shapes[i]->c_pt.x += point.x - pre_pt.x;
				shapes[i]->m_pt.x += point.x - pre_pt.x;
				shapes[i]->c_pt.y += point.y - pre_pt.y;
				shapes[i]->m_pt.y += point.y - pre_pt.y;

				Invalidate();
			}
		}

				pre_pt.x = point.x;
				pre_pt.y = point.y;

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
	onSelect = false;
	onRect = false;
	onCurve = false;
	onStar = false;
}


void CChildView::OnDrawRectangle()
{
	onRect = true;
	onSelect = false;
	onCircle = false;
	onCurve = false;
	onStar = false;
}


void CChildView::OnDrawCurve()
{
	onCurve = true;
	onSelect = false;
	onCircle = false;
	onRect = false;
	onStar = false;
}


void CChildView::OnDrawStar()
{
	onStar = true;
	onSelect = false;
	onCircle = false;
	onRect = false;
	onCurve = false;
}


void CChildView::OnActionSelect()
{
	onSelect = true;
	onStar = false;
	onCircle = false;
	onRect = false;
	onCurve = false;
}
