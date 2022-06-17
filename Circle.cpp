#include "pch.h"
#include "Circle.h"


Circle::Circle() : radius(0.0f)
{
}

void Circle::draw(CDC* pdc) {
	CBrush brush(color);
	pdc->SelectObject(brush);
	radius = sqrt((c_pt.x - m_pt.x) * (c_pt.x - m_pt.x) + (c_pt.y - m_pt.y) * (c_pt.y - m_pt.y));
	pdc->Ellipse(c_pt.x - radius, c_pt.y - radius, c_pt.x + radius, c_pt.y + radius);
}
