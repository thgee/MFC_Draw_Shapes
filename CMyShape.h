#pragma once
#include <vector>
class CMyShape
{

public:
	CMyShape();
	CPoint c_pt;
	CPoint m_pt;
	COLORREF color;
	bool selecting;
	void virtual draw(CDC* pdc);
	bool virtual inPos(CPoint pt);
	void virtual drawRect(CDC* pdc);
	
};

