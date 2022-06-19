#include "pch.h"
#include "CMyShape.h"

CMyShape::CMyShape() : m_pt(0,0) , c_pt(0,0), selecting(false) {
	color = RGB(10, 10, 255);
}

void CMyShape::draw(CDC* pdc) {

}
bool CMyShape::inPos(CPoint pt) {
	return false;
}

void CMyShape::drawRect(CDC* pdc) {

}


