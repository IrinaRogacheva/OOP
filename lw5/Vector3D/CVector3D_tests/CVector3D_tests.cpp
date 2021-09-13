#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CVector3D/CVector3D.h"
#include "float.h"
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

SCENARIO("Create default vector")
{
	CVector3D vector;
	CHECK(vector.x == 0);
	CHECK(vector.y == 0);
	CHECK(vector.z == 0);
}

SCENARIO("Create vector with coordinations x = 1, y = 2, z = 3")
{
	CVector3D vector(1, 2, 3);
	CHECK(vector.x == 1);
	CHECK(vector.y == 2);
	CHECK(vector.z == 3);
}

SCENARIO("Check vector's length")
{
	CVector3D vector(0, 4, 3);
	CHECK(vector.GetLength() == 5);
}

SCENARIO("Vector normalization")
{
	CVector3D vector(1, 2, -1);
	vector.Normalize();
	CHECK(abs(vector.x - 1.0 / sqrt(6)) <= DBL_EPSILON);
	CHECK(abs(vector.y - sqrt(2.0 / 3.0)) <= DBL_EPSILON);
	CHECK(abs(vector.z - -1.0 / sqrt(6)) <= DBL_EPSILON);
}

SCENARIO("Dot product")
{
	CVector3D vector1(1, 2, -3);
	CVector3D vector2(-6, 2.5, 0);
	CHECK(abs(DotProduct(vector1, vector2) - (-1)) <= DBL_EPSILON);
}

SCENARIO("Cross product")
{
	CVector3D vector1(1, 2, -3);
	CVector3D vector2(-6, 2.5, 0);
	CVector3D vector3 = CrossProduct(vector1, vector2);
	CHECK(abs(vector3.x - 7.5) <= DBL_EPSILON);
	CHECK(abs(vector3.y - 18) <= DBL_EPSILON);
	CHECK(abs(vector3.z - 14.5) <= DBL_EPSILON);
}

SCENARIO("v2 = -v1")
{
	CVector3D vector1(1, 2, -1);
	CVector3D vector2 = -vector1;
	CHECK(vector2.x == -vector1.x);
	CHECK(vector2.y == -vector1.y);
	CHECK(vector2.z == -vector1.z);
}

SCENARIO("v2 = +v1")
{
	CVector3D vector1(1, 2, -6);
	CVector3D vector2 = +vector1;
	CHECK(vector2.x == vector1.x);
	CHECK(vector2.y == vector1.y);
	CHECK(vector2.z == vector1.z);
}

SCENARIO("v1 + v2")
{
	CVector3D vector1(1, 2, -6);
	CVector3D vector2(-5, 0, -3);
	CVector3D vector3 = vector1 + vector2;
	CHECK(vector3.x == -4);
	CHECK(vector3.y == 2);
	CHECK(vector3.z == -9);
}

SCENARIO("v1 - v2")
{
	CVector3D vector1(3, 4, 1);
	CVector3D vector2(-2, 5, -3);
	CVector3D vector3 = vector1 - vector2;
	CHECK(vector3.x == 5);
	CHECK(vector3.y == -1);
	CHECK(vector3.z == 4);
}

SCENARIO("v1 += v2")
{
	CVector3D vector1(1, -3, 0);
	CVector3D vector2(21, 0.5, -1.2);
	vector1 += vector2;
	CHECK(abs(vector1.x - 22) <= DBL_EPSILON);
	CHECK(abs(vector1.y - (-2.5)) <= DBL_EPSILON);
	CHECK(abs(vector1.z - (-1.2)) <= DBL_EPSILON);
}

SCENARIO("v1 -= v2")
{
	CVector3D vector1(26, -3, 0);
	CVector3D vector2(21, 0.5, -1.2);
	vector1 -= vector2;
	CHECK(abs(vector1.x - 5) <= DBL_EPSILON);
	CHECK(abs(vector1.y - (-3.5)) <= DBL_EPSILON);
	CHECK(abs(vector1.z - 1.2) <= DBL_EPSILON);
}

SCENARIO("v1 * 20")
{
	CVector3D vector1(1, 2, 3.7);
	CVector3D vector2 = vector1 * 20;
	CHECK(abs(vector2.x - 20) <= DBL_EPSILON);
	CHECK(abs(vector2.y - 40) <= DBL_EPSILON);
	CHECK(abs(vector2.z - 74.0) <= DBL_EPSILON);
}

SCENARIO("20 * v1")
{
	CVector3D vector1(1, 2, 3.7);
	CVector3D vector2 = 20 * vector1;
	CHECK(abs(vector2.x - 20) <= DBL_EPSILON);
	CHECK(abs(vector2.y - 40) <= DBL_EPSILON);
	CHECK(abs(vector2.z - 74.0) <= DBL_EPSILON);
}

SCENARIO("v1 / 1.6")
{
	CVector3D vector1(2, 4, 6);
	CVector3D vector2 = vector1 / 1.6;
	CHECK(abs(vector2.x - 1.25) <= DBL_EPSILON);
	CHECK(abs(vector2.y - 2.5) <= DBL_EPSILON);
	CHECK(abs(vector2.z - 3.75) <= DBL_EPSILON);
}

SCENARIO("v1 *= 1.6")
{
	CVector3D vector1(0, 2, 1.2);
	vector1 *= 1.6;
	CHECK(abs(vector1.x - 0) <= DBL_EPSILON);
	CHECK(abs(vector1.y - 3.2) <= DBL_EPSILON);
	CHECK(abs(vector1.z - 1.92) <= DBL_EPSILON);
}

SCENARIO("v1 /= -0.5")
{
	CVector3D vector1(0.32, 10, -2);
	vector1 /= -0.5;
	CHECK(abs(vector1.x - (-0.64)) <= DBL_EPSILON);
	CHECK(abs(vector1.y - (-20)) <= DBL_EPSILON);
	CHECK(abs(vector1.z - 4) <= DBL_EPSILON);
}

SCENARIO("v1 == v2")
{
	CVector3D vector1(1, -2, 1);
	CVector3D vector2(1, -2, 1);
	CHECK(vector1 == vector2);
}

SCENARIO("v1 != v2")
{
	CVector3D vector1(1, -2, 1);
	CVector3D vector2(1, 2, 1);
	CHECK((vector1 != vector2));
}

SCENARIO("output << v")
{
	CVector3D vector(1, 2, 3);
	ostringstream output;
	output << vector;
	CHECK(output.str() == "1, 2, 3");
}

SCENARIO("input >> v")
{
	CVector3D vector;
	istringstream input("3, 5, 7");
	input >> vector;
	CHECK(vector.x == 3);
	CHECK(vector.y == 5);
	CHECK(vector.z == 7);
}