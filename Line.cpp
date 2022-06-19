#include "pch.h"
#include "Line.h"

Line::Line() {}

void Line::draw(CDC* pdc) {
	CBrush brush(color);
	CPen pen(PS_SOLID, 3, color);
	pdc->SelectObject(pen);
	for (int i = 0; i < pt2.size(); i++) {
		pdc->MoveTo(pt1[i].x, pt1[i].y);
		pdc->LineTo(pt2[i].x, pt2[i].y);
	}
}




bool Line::inPos(CPoint pt) {
	for (int i = 0; i < pt2.size(); i++) {
		if ((pt1[i].x + 5 > pt.x && pt1[i].x - 5 < pt.x &&
			pt1[i].y + 5 > pt.y && pt1[i].y - 5 < pt.y))
			return true;
	}
	return false;
}

void Line::drawRect(CDC* pdc) {
	CPen pen(PS_DASH, 1, RGB(0, 0, 0));
	pdc->SelectStockObject(NULL_BRUSH);
	pdc->SelectObject(pen);

	float max_x = pt1[0].x, min_x = pt1[0].x, max_y = pt1[0].y, min_y = pt1[0].y;
	for (int i = 0; i < pt1.size(); i++) {
		if (max_x < pt1[i].x) max_x = pt1[i].x;
		if (min_x > pt1[i].x) min_x = pt1[i].x;
		if (max_y < pt1[i].y) max_y = pt1[i].y;
		if (min_y > pt1[i].y) min_y = pt1[i].y;
	}
	pdc->Rectangle(min_x - 5, min_y - 5, max_x + 5, max_y + 5);
}



