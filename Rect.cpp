#include "pch.h"
#include "Rect.h"

Rect::Rect() {}

void Rect::draw(CDC* pdc){
	CBrush brush(color);
	pdc->SelectObject(brush);
	width = m_pt.x - c_pt.x;
	height = m_pt.y - c_pt.y;
	pdc->Rectangle(c_pt.x, c_pt.y, c_pt.x + width, c_pt.y + height);
}
