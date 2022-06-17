#pragma once
#include <vector>
class CMyShape
{

public:
	CMyShape();
	CPoint c_pt;
	CPoint m_pt;
	COLORREF color;
	void virtual draw(CDC* pdc);
};

