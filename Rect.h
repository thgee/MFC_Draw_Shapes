#pragma once
#include "CMyShape.h"
class Rect : public CMyShape
{
public:
	Rect();
	float width;
	float height;

	void draw(CDC* pdc);
};

