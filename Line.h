#pragma once
#include <vector>
#include "CMyShape.h"
class Line : public CMyShape
{
public:
	Line();
	void draw(CDC* pdc);
	std::vector <CPoint>pt1; // 선의 시작좌표
	std::vector <CPoint>pt2; // 선의 끝좌표

	bool inPos(CPoint pt);
	void drawRect(CDC* pdc);

};

