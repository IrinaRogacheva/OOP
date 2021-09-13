#pragma once
#include "CPoint.h"
#include "IShape.h"

class CLineSegment final : public IShape
{
public:
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t lineColor);
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	uint32_t GetOutlineColor() const override;

	void Draw(ICanvas& canvas) const override;
private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_color;
};