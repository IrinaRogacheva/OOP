#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CShapeControl.h"
#include <sstream>
#include <functional>
#include <algorithm>
#include <memory>
#include "CCanvas.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace std::placeholders;

CShapeControl::CShapeControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap(
		  {
			  { "line", bind(&CShapeControl::CreateLineFromInput, this, _1) },
			  { "rectangle", bind(&CShapeControl::CreateRectangleFromInput, this, _1) },
			  { "triangle", bind(&CShapeControl::CreateTriangleFromInput, this, _1) },
			  { "circle", bind(&CShapeControl::CreateCircleFromInput, this, _1) },
		  })
{
}

void CShapeControl::HandleCommand()
{
	string consoleLine;
	getline(m_input, consoleLine);
	istringstream stream(consoleLine);

	string action;
	stream >> action;

	auto it = m_actionMap.find(action);
	if (it == m_actionMap.end())
	{
		throw invalid_argument("Unknown command");
	}
	
	return it->second(stream);
}

void CShapeControl::CreateLineFromInput(std::istream& args)
{
	double x1, y1, x2, y2;
	uint32_t colour;
	args >> x1 >> y1 >> x2 >> y2 >> hex >> colour;
	if (args.fail())
	{
		throw invalid_argument("Incorrect input");
	}

	CLineSegment line({ x1, y1 }, { x2, y2 }, colour);
	m_shapes.push_back(make_shared<CLineSegment>(line));
}

void CShapeControl::CreateRectangleFromInput(std::istream& args)
{
	double x, y, width, height;
	uint32_t outlineColour, fillColour;
	args >> x >> y >> width >> height >> hex >> outlineColour >> hex >> fillColour;
	if (args.fail())
	{
		throw invalid_argument("Incorrect input");
	}

	CRectangle rectangle({ x, y }, width, height, outlineColour, fillColour);
	m_shapes.push_back(make_shared<CRectangle>(rectangle));
}

void CShapeControl::CreateTriangleFromInput(std::istream& args)
{
	vector<CPoint> trianglePoints;
	for (size_t i = 0; i < 3; i++)
	{
		double x, y;
		args >> x >> y;
		if (args.fail())
		{
			throw invalid_argument("Incorrect input");
		}
		trianglePoints.push_back({ x, y });
	}

	uint32_t outlineColour, fillColour;
	args >> hex >> outlineColour >> hex >> fillColour;
	if (args.fail())
	{
		throw invalid_argument("Incorrect input");
	}

	CTriangle triangle(trianglePoints[0], trianglePoints[1], trianglePoints[2], outlineColour, fillColour);
	m_shapes.push_back(make_shared<CTriangle>(triangle));
}

void CShapeControl::CreateCircleFromInput(std::istream& args)
{
	double x, y, radius;
	uint32_t outlineColour, fillColour;
	args >> x >> y >> radius >> hex >> outlineColour >> hex >> fillColour;
	if (args.fail())
	{
		throw invalid_argument("Incorrect input");
	}

	CCircle circle({ x, y }, radius, outlineColour, fillColour);
	m_shapes.push_back(make_shared<CCircle>(circle));
}

void CShapeControl::FindShapeWithMaxArea() const
{
	if (m_shapes.empty())
	{
		return;
	}

	auto maxAreaShape = std::max_element(m_shapes.begin(), m_shapes.end(), [](const auto& first, const auto& second) {
		return first->GetArea() < second->GetArea();
	});

	m_output << "The shape with the maximum area:" << endl;
	m_output << (*maxAreaShape)->ToString();
}

void CShapeControl::FindShapeWithMinPerimeter() const
{
	if (m_shapes.empty())
	{
		return;
	}

	auto minPerimeterShape = std::min_element(m_shapes.begin(), m_shapes.end(), [](const auto& first, const auto& second) {
		return first->GetPerimeter() < second->GetPerimeter();
	});
	m_output << "The shape with the minimum perimeter:" << endl;
	m_output << (*minPerimeterShape)->ToString();
}

void CShapeControl::Draw() const
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(600, 600), "Shapes");
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(255, 255, 255));

		for (auto it = m_shapes.begin(); it != m_shapes.end(); it++)
		{
			(*it)->Draw(canvas);
		}

		window.display();
	}
}
