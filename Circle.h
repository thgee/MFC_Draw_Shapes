#pragma once
#include "CMyShape.h"
class Circle : public CMyShape{
public:
	Circle();
	float radius;
	void draw(CDC* pdc);
	
};

