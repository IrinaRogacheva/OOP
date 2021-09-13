#include "CCanvas.h"

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(const CPoint& first, const CPoint& second, uint32_t outlineColor)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f((float)first.GetX(), (float)first.GetY());
	line[1].position = sf::Vector2f((float)second.GetX(), (float)second.GetY());

	line[0].color = GetColor(outlineColor);
	line[1].color = GetColor(outlineColor);

	m_window.draw(line);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor)
{
	sf::ConvexShape shape;
	shape.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); i++)
	{
		shape.setPoint(i, sf::Vector2f((float)points[i].GetX(), (float)points[i].GetY()));
	}

	shape.setFillColor(GetColor(fillColor));

	m_window.draw(shape);
}


void CCanvas::DrawCircle(CPoint const& centre, double radius, uint32_t outlineColor)
{
	sf::CircleShape circle;

	circle.setOrigin((float)radius, (float)radius);
	circle.setPosition((float)centre.GetX(), (float)centre.GetY());
	circle.setRadius((float)radius);

	circle.setOutlineThickness(1);
	circle.setOutlineColor(GetColor(outlineColor));

	m_window.draw(circle);
}

void CCanvas::FillCircle(CPoint const& centre, double radius, uint32_t fillColor)
{
	sf::CircleShape circle;

	circle.setOrigin((float)radius, (float)radius);
	circle.setPosition((float)centre.GetX(), (float)centre.GetY());
	circle.setRadius((float)radius);

	circle.setFillColor(GetColor(fillColor));

	m_window.draw(circle);
}

sf::Color CCanvas::GetColor(uint32_t color) const
{
	uint32_t r = (color >> 16) & 255;
	uint32_t g = (color >> 8) & 255;
	uint32_t b = color & 255;

	return sf::Color(r, g, b);
}
