#pragma once
#include "CMyShape.h"
class Star : public CMyShape
{

public:
	Star();
	float long_dist; // star�� �߽ɰ� ������ �������� �Ÿ�
	float short_dist;
	CPoint vtx[10]; // Star�� �� �������� ��ǥ�� �־��� �迭
	void draw(CDC* pdc);
	bool inPos(CPoint pt);
	


};

