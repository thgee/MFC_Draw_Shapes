#pragma once
#include "CMyShape.h"
class Star : public CMyShape
{

public:
	Star();
	float long_dist; // star의 중심과 꼭짓점 끝까지의 거리
	float short_dist;
	CPoint vtx[10]; // Star의 각 꼭짓점의 좌표를 넣어줄 배열
	void draw(CDC* pdc);
	bool inPos(CPoint pt);
	


};

