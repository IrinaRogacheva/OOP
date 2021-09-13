#pragma once
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle final: public ISolidShape
{
public:
	double GetPerimeter() const override;
	uint32_t GetFillColor() const override;
	uint32_t GetOutlineColor() const override;
	double GetArea() const override;
	std::string ToString() const override; 

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

	CRectangle(const CPoint& leftTop, double width, double height, uint32_t outlineColor, uint32_t fillColor);

	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_leftTopPoint;
	double m_width;
	double m_height;
	uint32_t m_fillColor;
	uint32_t m_outlineColor;
};
