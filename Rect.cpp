#include "pch.h"
#include "Rect.h"

Rect::Rect() {}

void Rect::draw(CDC* pdc){
	CPen pen(PS_SOLID, 3,RGB(0, 0, 0));
	pdc->SelectObject(pen);
	CBrush brush(color);
	pdc->SelectObject(brush);
	width = m_pt.x - c_pt.x;
	height = m_pt.y - c_pt.y;
	pdc->Rectangle(c_pt.x, c_pt.y, c_pt.x + width, c_pt.y + height);
}


void Rect::drawRect(CDC* pdc) {
	CPen pen(PS_DASH, 1, RGB(0, 0, 0));
	pdc->SelectStockObject(NULL_BRUSH);

	pdc->SelectObject(pen);
	pdc->Rectangle(c_pt.x - 5, c_pt.y - 5, c_pt.x + width  +5, c_pt.y + height + 5);
}


bool Rect::inPos(CPoint pt) {
	if (pt.x <= c_pt.x + width && pt.x >= c_pt.x && pt.y >= c_pt.y && pt.y <= c_pt.y + height) return true;
	else return false;
}