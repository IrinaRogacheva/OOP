#pragma once
#include <string>

class CPoint final
{
public:
	CPoint(double x, double y);
	double GetX() const;
	double GetY() const;
	std::string ToString() const;

private:
	double x;
	double y;
};

bool operator==(const CPoint& point1, const CPoint point2);
