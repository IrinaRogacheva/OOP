#include "CVector3D.h"
#include "float.h"
#include <string>

CVector3D::CVector3D(double x0, double y0, double z0)
	: x(x0)
	, y(y0)
	, z(z0)
{
}

CVector3D const CVector3D::operator-() const
{
	return CVector3D(-x, -y, -z);
}

CVector3D const CVector3D::operator+() const
{
	return *this;
}

CVector3D const CVector3D::operator+(CVector3D const& vector2) const
{
	return CVector3D(x + vector2.x, y + vector2.y, z + vector2.z);
}

CVector3D const CVector3D::operator-(CVector3D const& vector2) const
{
	return CVector3D(x - vector2.x, y - vector2.y, z - vector2.z);
}

const CVector3D& CVector3D::operator+=(CVector3D const& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

const CVector3D& CVector3D::operator-=(CVector3D const& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

CVector3D const CVector3D::operator*(double scalar) const
{
	return CVector3D(x * scalar, y * scalar, z * scalar);
}

CVector3D const CVector3D::operator/(double scalar) const
{
	return CVector3D(x / scalar, y / scalar, z / scalar);
}

const CVector3D& CVector3D::operator*=(double scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

const CVector3D& CVector3D::operator/=(double scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

bool CVector3D::operator==(CVector3D const& other) const
{
	return ((abs(x - other.x) <= DBL_EPSILON) && (abs(y - other.y) <= DBL_EPSILON) && (abs(z - other.z) <= DBL_EPSILON));
}

bool CVector3D::operator!=(CVector3D const& other) const
{
	return ((abs(x - other.x) > DBL_EPSILON) || (abs(y - other.y) > DBL_EPSILON) || (abs(z - other.z) > DBL_EPSILON));
}

double CVector3D::GetLength() const
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void CVector3D::Normalize()
{
	double vLength = GetLength();
	if (vLength > 0)
	{
		x /= vLength;
		y /= vLength;
		z /= vLength;
	}
}

std::ostream& operator<<(std::ostream& output, const CVector3D& vector)
{
	output << vector.x << ", " << vector.y << ", " << vector.z;
	return output;
}

std::istream& operator>>(std::istream& input, CVector3D& vector)
{
	std::string str;
	input >> vector.x >> str;
	input >> vector.y >> str;
	input >> vector.z;
	return input;
}

CVector3D const operator*(double scalar, CVector3D const& vector)
{
	return vector * scalar;
}

double DotProduct(CVector3D const& v1, CVector3D const& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

CVector3D CrossProduct(CVector3D const& v1, CVector3D const& v2)
{
	return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}