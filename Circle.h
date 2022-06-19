#pragma once
#include "CMyShape.h"
#include "Rect.h"

class Circle : public CMyShape {
public:
	Circle();
	float radius;
	bool inPos(CPoint pt);
	void draw(CDC* pdc);
	void drawRect(CDC* pdc);
};
