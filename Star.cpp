#include "pch.h"
#include "Star.h"

Star::Star() :long_dist(0.0f), short_dist(0.0f) {}


void Star::draw(CDC* pdc) {
	
	CBrush brush(color);


	// 별 내부 색칠
	CRgn rgn;
	rgn.CreatePolygonRgn(vtx, 10, ALTERNATE);
	pdc->PaintRgn(&rgn);
	pdc->SelectObject(brush);

	// 별 외곽선
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	pdc->SelectObject(pen);
	for (int i = 0; i < 10; i++) {
		pdc->MoveTo(vtx[i]);
		if (i == 9) {
			pdc->LineTo(vtx[0]);
			break;
		}
		// vtx[9] 에서 vtx[0]으로 선을 이어주기 위함
		pdc->LineTo(vtx[i + 1]);
	}

}

bool Star::inPos(CPoint pt) {  // 직선의 방정식으로 pos함수 구현 하다가 포기..
	/*if (pt.y > (vtx[1].y - vtx[2].y) / (vtx[1].x - vtx[2].x) * (pt.x - vtx[1].x) + vtx[1].y && 
		pt.y > (vtx[2].y - vtx[3].y) / (vtx[2].x - vtx[3].x) * (pt.x - vtx[2].x) + vtx[2].y && 
		pt.y < (vtx[3].y - vtx[1].y) / (vtx[3].x - vtx[1].x) * (pt.x - vtx[1].x) + vtx[1].y)
		return true;

	else if 
		(pt.y <(vtx[3].y - vtx[4].y) / (vtx[3].x - vtx[4].x) * (pt.x - vtx[3].x) + vtx[3].y &&
		pt.y > (vtx[4].y - vtx[5].y) / (vtx[4].x - vtx[5].x) * (pt.x - vtx[4].x) + vtx[4].y &&
		pt.y < (vtx[3].y - vtx[5].y) / (vtx[3].x - vtx[5].x) * (pt.x - vtx[3].x) + vtx[3].y)
		return true;*/


	return false;
}

