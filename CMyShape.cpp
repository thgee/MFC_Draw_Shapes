#include "pch.h"
#include "CMyShape.h"

CMyShape::CMyShape() : m_pt(0,0) , c_pt(0,0) {
	color = RGB(10, 10, 255);
}

void CMyShape::draw(CPaintDC* pdc) {

}