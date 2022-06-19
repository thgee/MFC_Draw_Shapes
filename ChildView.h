
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include "CMyShape.h"
#include "Circle.h"
#include "Line.h"
#include "Star.h"

#include <vector>


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();
	// --------------------------------------------------
	bool onRect;
	bool onCircle;
	bool onStar;
	bool onCurve;
	bool onSelect;
	CPoint pre_pt; // 이동하기 전의 좌표를 저장하는 변수



	std::vector <CMyShape*> shapes;
	
	float DegToRad(float deg);
	void SetColor();
	int getSelectNum();

	// 
// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawRectangle();
	afx_msg void OnDrawCurve();
	afx_msg void OnDrawStar();
	afx_msg void OnActionSelect();
};

