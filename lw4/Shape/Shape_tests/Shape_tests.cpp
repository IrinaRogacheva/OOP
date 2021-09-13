#define CATCH_CONFIG_MAIN
#include "fakeit.hpp"

#include "../Shape/CCircle.h"
#include "../Shape/CLineSegment.h"
#include "../Shape/CRectangle.h"
#include "../Shape/CTriangle.h"
#include "../Shape/CShapeControl.h"
#include <string>

TEST_CASE("Create CLineSegment")
{
	CLineSegment line({ -1, 1 }, { 1, 1 }, 0x000000);

	CHECK(line.GetArea() == 0);
	CHECK(round(line.GetPerimeter() * 1000) / 1000 == 2.0);
	CHECK(line.GetOutlineColor() == 0x000000);
	CHECK(line.GetStartPoint().GetX() == -1);
	CHECK(line.GetStartPoint().GetY() == 1);
	CHECK(line.GetEndPoint().GetX() == 1);
	CHECK(line.GetEndPoint().GetY() == 1);
}

TEST_CASE("Create CTriangle")
{
	CTriangle triangle({ -1, 1 }, { -1, -1 }, { 1, -1 }, 0x000000, 0xFFFFFF);

	CHECK(round(triangle.GetArea() * 1000) / 1000 == 2.000);
	CHECK(round(triangle.GetPerimeter() * 1000) / 1000 == 6.828);
	CHECK(triangle.GetOutlineColor() == 0x000000);
	CHECK(triangle.GetFillColor() == 0xffffff);
	CHECK(triangle.GetVertex1().GetX()== -1);
	CHECK(triangle.GetVertex1().GetY() == 1);
	CHECK(triangle.GetVertex2().GetX() == -1);
	CHECK(triangle.GetVertex2().GetY() == -1);
	CHECK(triangle.GetVertex3().GetX() == 1);
	CHECK(triangle.GetVertex3().GetY() == -1);
}

TEST_CASE("Create CRectangle")
{
	CRectangle rectangle({ -2, 1 }, 3, 2, 0x000000, 0xFFFFFF);

	CHECK(round(rectangle.GetArea() * 1000) / 1000 == 6.000);
	CHECK(round(rectangle.GetPerimeter() * 1000) / 1000 == 10.000);
	CHECK(rectangle.GetOutlineColor() == 0x000000);
	CHECK(rectangle.GetFillColor() == 0xFFFFFF);
	CHECK(rectangle.GetLeftTop().GetX() == -2);
	CHECK(rectangle.GetLeftTop().GetY() == 1);
	CHECK(rectangle.GetRightBottom().GetX() == 1);
	CHECK(rectangle.GetRightBottom().GetY() == -1);
	CHECK(rectangle.GetWidth() == 3);
	CHECK(rectangle.GetHeight() == 2);
}

TEST_CASE("Create CCircle")
{
	CCircle circle({ 0, 0 }, 3, 0x000000, 0xFFFFFF);

	CHECK(round(circle.GetArea() * 1000) / 1000 == 28.274);
	CHECK(round(circle.GetPerimeter() * 1000) / 1000 == 18.85);
	CHECK(circle.GetOutlineColor() == 0x000000);
	CHECK(circle.GetFillColor() == 0xFFFFFF);
	CHECK(circle.GetCenter().GetX() == 0);
	CHECK(circle.GetCenter().GetY() == 0);
	CHECK(circle.GetRadius() == 3);
}

TEST_CASE("Input line parametrs")
{
	std::stringstream input, output;
	CShapeControl control(input, output);
	input << "line 0 1 -1 -1 ff0000 00ff00";
	CHECK_NOTHROW(control.HandleCommand());
}

TEST_CASE("Input rectangle parametrs")
{
	std::stringstream input, output;
	CShapeControl control(input, output);
	input << "rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00";
	CHECK_NOTHROW(control.HandleCommand());
}

TEST_CASE("Input triangle parametrs")
{
	std::stringstream input, output;
	CShapeControl control(input, output);
	input << "triangle 10.3 20.15 30.7 40.4 47.6 88.9 ff0000 00ff00";
	CHECK_NOTHROW(control.HandleCommand());
}

TEST_CASE("Input circle parametrs")
{
	std::stringstream input, output;
	CShapeControl control(input, output);
	input << "circle 0 0 2 ff0000 00ff00";
	CHECK_NOTHROW(control.HandleCommand());
}

TEST_CASE("Input with missing parameter")
{
	std::stringstream input, output;
	CShapeControl control(input, output);
	input << "circle 0 0 ff0000 00ff00";
	CHECK_THROWS(control.HandleCommand());
}

TEST_CASE("Incorrect input")
{
	std::stringstream input, output;
	CShapeControl control(input, output);
	input << "circle 0 r 56 ff0000 00ff00";
	CHECK_THROWS(control.HandleCommand());
}

TEST_CASE("Unknown command")
{
	std::stringstream input, output;
	CShapeControl control(input, output);
	input << "something 0 5 56 ff0000 00ff00";
	CHECK_THROWS(control.HandleCommand());
}

TEST_CASE("Find the shape with the maximum area")
{
	std::stringstream input, output;
	CShapeControl control(input, output);

	input << "circle 0 0 3 ff0000 00ff00";
	control.HandleCommand();
	input.clear();
	
	input << "circle 0 0 5 ff0000 00ff00";
	control.HandleCommand();

	control.FindShapeWithMaxArea();

	std::string expectedOutput = std::string("The shape with the maximum area:\n")
		+ "circle:\n"
		+ "\tperimeter = 31.415927\n"
		+ "\tarea = 78.539816\n"
		+ "\tfill color = 00ff00\n"
		+ "\toutline color = ff0000\n"
		+ "\tradius = 5.000000\n"
		+ "\tcenter = (0.000000, 0.000000)\n";
	CHECK(output.str() == expectedOutput);
}

TEST_CASE("Find the shape with the minimum perimeter")
{
	std::stringstream input, output;
	CShapeControl control(input, output);

	input << "triangle 0 0 200 200 0 400 ff0000 00ff00";
	control.HandleCommand();
	input.clear();

	input << "triangle 0 0 300 300 0 400 ff0000 00ff00";
	control.HandleCommand();

	control.FindShapeWithMinPerimeter();

	std::string expectedOutput = std::string("The shape with the minimum perimeter:\n")
		+ "triangle:\n"
		+ "\tperimeter = 965.685425\n"
		+ "\tarea = 40000.000000\n"
		+ "\tfill color = 00ff00\n"
		+ "\toutline color = ff0000\n"
		+ "\tvertex1 = (0.000000, 0.000000)\n"
		+ "\tvertex2 = (200.000000, 200.000000)\n"
		+ "\tvertex3 = (0.000000, 400.000000)\n";
	CHECK(output.str() == expectedOutput);
}

TEST_CASE("Draw a line")
{
	CPoint first{ 10.5, 40.6 };
	CPoint second{ 30.6, 78 };
	uint32_t color = 0xffffff;
	CLineSegment line(first, second, color);

	fakeit::Mock<ICanvas> canvas;
	fakeit::Fake(Method(canvas, DrawLine));
	ICanvas& i = canvas.get();
	line.Draw(i);
	fakeit::Verify(Method(canvas, DrawLine)).Once();

	fakeit::Verify(Method(canvas, DrawLine).Using(first, second, 0xffffff));
}

TEST_CASE("Draw a circle")
{
	CPoint center(1.2, 3.4);
	CCircle circle(center, 3, 0xff0000, 0x00ff00);

	fakeit::Mock<ICanvas> canvas;
	fakeit::Fake(Method(canvas, DrawCircle));
	fakeit::Fake(Method(canvas, FillCircle));
	ICanvas& i = canvas.get();
	circle.Draw(i);
	fakeit::Verify(Method(canvas, DrawCircle)).Once();
	fakeit::Verify(Method(canvas, FillCircle)).Once();

	fakeit::Verify(Method(canvas, DrawCircle).Using(center, 3, 0xff0000));
	fakeit::Verify(Method(canvas, FillCircle).Using(center, 3, 0x00ff00));
}

TEST_CASE("Draw a rectangle")
{
	CPoint leftTopPoint(1.2, 3.4);
	double width = 9.2;
	double height = 4.1;
	CRectangle rectangle(leftTopPoint, width, height, 0xff0000, 0x00ff00);

	fakeit::Mock<ICanvas> canvas;
	fakeit::Fake(Method(canvas, FillPolygon));
	fakeit::Fake(Method(canvas, DrawLine));
	ICanvas& i = canvas.get();
	rectangle.Draw(i);
	fakeit::Verify(Method(canvas, FillPolygon) + Method(canvas, DrawLine) + Method(canvas, DrawLine) + Method(canvas, DrawLine) + Method(canvas, DrawLine)).Once();
}

TEST_CASE("Draw a triangle")
{
	CPoint point1(1.2, 3.4);
	CPoint point2(5.6, 7.8);
	CPoint point3(9.0, 1.2);
	CTriangle triangle(point1, point2, point3, 0x123456, 0x987654);

	fakeit::Mock<ICanvas> canvas;
	fakeit::Fake(Method(canvas, FillPolygon));
	fakeit::Fake(Method(canvas, DrawLine));
	ICanvas& i = canvas.get();
	triangle.Draw(i);
	fakeit::Verify(Method(canvas, FillPolygon) + Method(canvas, DrawLine) + Method(canvas, DrawLine) + Method(canvas, DrawLine)).Once();
}
