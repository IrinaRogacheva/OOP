#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);

	void DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor) override;
	void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) override;
	void DrawCircle(CPoint const& centre, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint const& centre, double radius, uint32_t fillColor) override;

private:
	sf::Color GetColor(uint32_t color) const;

	sf::RenderWindow& m_window;
};