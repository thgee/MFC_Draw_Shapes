#include "pch.h"
#include "Circle.h"


Circle::Circle() : radius(0.0f)
{
}

void Circle::draw(CDC* pdc) {
	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	pdc->SelectObject(pen);
	CBrush brush(color);
	pdc->SelectObject(brush);
	radius = sqrt((c_pt.x - m_pt.x) * (c_pt.x - m_pt.x) + (c_pt.y - m_pt.y) * (c_pt.y - m_pt.y));
	pdc->Ellipse(c_pt.x - radius, c_pt.y - radius, c_pt.x + radius, c_pt.y + radius);
}

void Circle::drawRect(CDC* pdc) {
	CPen pen(PS_DASH, 1, RGB(0, 0, 0));
	pdc->SelectStockObject(NULL_BRUSH);

	pdc->SelectObject(pen);
	pdc->Rectangle(c_pt.x - radius - 3, c_pt.y - radius - 3, c_pt.x + radius + 3, c_pt.y + radius + 3);
}


bool Circle::inPos(CPoint pt) {
	float dis = sqrt((c_pt.x - pt.x) * (c_pt.x - pt.x) + (c_pt.y - pt.y) * (c_pt.y - pt.y));
	if (dis <= radius) return true;
	else return false;
}
