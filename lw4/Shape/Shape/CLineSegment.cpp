#include "CLineSegment.h"
#include <iomanip>
#include <sstream>

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t lineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_color(lineColor)
{
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_startPoint.GetX() - m_endPoint.GetX(), 2) + pow(m_startPoint.GetY() - m_endPoint.GetY(), 2));
}

std::string CLineSegment::ToString() const
{
	std::ostringstream strm;
	strm << "line:\n"
		 << std::setprecision(6) << std::fixed
		 << "\tperimeter = " << GetPerimeter() << "\n"
		 << "\tarea = " << GetArea() << "\n"
		 << "\tcolor = " << std::hex << std::setw(6) << std::setfill('0') << GetOutlineColor() << "\n"
		 << "\tstart point = " << m_startPoint.ToString() << "\n"
		 << "\tend point = " << m_endPoint.ToString() << "\n";

	return strm.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_color;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_color);
}
