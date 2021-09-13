#pragma once
#include <fstream>
#include <iostream>

class CVector3D
{
public:
	CVector3D() = default;
	CVector3D(double x0, double y0, double z0);
	double GetLength() const;
	void Normalize();
	CVector3D const operator-() const;
	CVector3D const operator+() const;
	CVector3D const operator+(CVector3D const& vector2) const;
	CVector3D const operator-(CVector3D const& vector2) const;
	const CVector3D& operator+=(CVector3D const& vector);
	const CVector3D& operator-=(CVector3D const& vector);
	CVector3D const operator*(double scalar) const;
	CVector3D const operator/(double scalar) const;
	const CVector3D& operator*=(double scalar);
	const CVector3D& operator/=(double scalar);
	bool operator==(CVector3D const& other) const;
	bool operator!=(CVector3D const& other) const;
	double x = 0, y = 0, z = 0;
};

CVector3D const operator*(double scalar, CVector3D const& vector);

std::istream& operator>>(std::istream& input, CVector3D& vector);

std::ostream& operator<<(std::ostream& output, const CVector3D& vector);

double DotProduct(CVector3D const& v1, CVector3D const& v2);

CVector3D CrossProduct(CVector3D const& v1, CVector3D const& v2);
