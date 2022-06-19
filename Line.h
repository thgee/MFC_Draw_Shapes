#pragma once
#include <vector>
#include "CMyShape.h"
class Line : public CMyShape
{
public:
	Line();
	void draw(CDC* pdc);
	std::vector <CPoint>pt1; // ���� ������ǥ
	std::vector <CPoint>pt2; // ���� ����ǥ

	bool inPos(CPoint pt);
	void drawRect(CDC* pdc);

};

