#pragma once
#include "CPoint.h"
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() {}
	virtual void DrawLine(CPoint const& first, CPoint const& second, uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint const& centre, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(CPoint const& centre, double radius, uint32_t fillColor) = 0;
};