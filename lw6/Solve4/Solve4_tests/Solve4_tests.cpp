#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Solve4/Solve4.h"

SCENARIO("Invalid argument. The coefficient at x^4 cannot be equal to 0")
{
	CHECK_THROWS_AS(Solve4(0, 1, 2, 3, 4), std::invalid_argument);
}

SCENARIO("When solving the equation of degree 3, the coefficient s < 0 and q > 0")
{
	EquationRoot4 EquationRoot = Solve4(1, 2, -4, 6, 6);
	CHECK(EquationRoot.roots[0] - (-0.653102) < 0.00001);
	CHECK(EquationRoot.roots[1] - (-3.4951) < 0.00001);
	CHECK(EquationRoot.numRoots == 2);
}

SCENARIO("When solving the equation of degree 3, the coefficient s < 0 and q < 0")
{
	EquationRoot4 EquationRoot = Solve4(-10, -7, 5, 78, 478);
	CHECK(EquationRoot.roots[0] - 2.76436 < 0.00001);
	CHECK(EquationRoot.roots[1] - (-2.55835) < 0.00001);
	CHECK(EquationRoot.numRoots == 2);
}

SCENARIO("When solving the equation of degree 3, the coefficient s < 0 and q = 0")
{
	EquationRoot4 EquationRoot = Solve4(1, 2, 0, 0, 0);
	CHECK(EquationRoot.roots[0] - 0 < 0.00001);
	CHECK(EquationRoot.roots[1] - (-2) < 0.00001);
	CHECK(EquationRoot.roots[2] - 0 < 0.00001);
	CHECK(EquationRoot.numRoots == 3);
}

SCENARIO("When solving the equation of degree 3, the coefficient s = 0")
{
	EquationRoot4 EquationRoot = Solve4(1, 0, 0, 0, 0);
	CHECK(EquationRoot.roots[0] - 0 < 0.00001);
	CHECK(EquationRoot.roots[1] - 0 < 0.00001);
	CHECK(EquationRoot.numRoots == 2);
}

SCENARIO("When solving equation of the second degree, the condition a4 / 2 * y - c4 < 0 is not fulfilled")
{
	EquationRoot4 EquationRoot = Solve4(1, -2, 34, -47, 5);
	CHECK(EquationRoot.roots[0] - 1.30442 < 0.00001);
	CHECK(EquationRoot.roots[1] - 0.116065 < 0.00001);
	CHECK(EquationRoot.numRoots == 2);
}

SCENARIO("When solving equation of the second degree, the condition a4 / 2 * y - c4 < 0 is fulfilled")
{
	EquationRoot4 EquationRoot = Solve4(1, -7, 8, 75, 7);
	CHECK(EquationRoot.roots[0] - (-0.0943626) < 0.00001);
	CHECK(EquationRoot.roots[1] - (-2.37801) < 0.00001);
	CHECK(EquationRoot.numRoots == 2);
}

SCENARIO("The discriminants of both equations are greater than zero")
{
	EquationRoot4 EquationRoot = Solve4(3, 6, -123, -126, 1080);
	CHECK(EquationRoot.roots[2] - 5 < 0.00001);
	CHECK(EquationRoot.roots[3] - 3 < 0.00001);
	CHECK(EquationRoot.roots[0] - (-4) < 0.00001);
	CHECK(EquationRoot.roots[1] - (-6) < 0.00001);
	CHECK(EquationRoot.numRoots == 4);
}

SCENARIO("The discriminant of one of the equations of the second degree is 0")
{
	EquationRoot4 EquationRoot = Solve4(1, 0, -1, 0, 0);
	CHECK(EquationRoot.roots[0] - 0 < 0.00001);
	CHECK(EquationRoot.roots[1] - 1 < 0.00001);
	CHECK(EquationRoot.roots[2] - (-1) < 0.00001);
	CHECK(EquationRoot.numRoots == 3);
}

SCENARIO("The discriminant of one equation of the second degree is greater than zero, and the other is less than")
{
	EquationRoot4 EquationRoot = Solve4(1, 4, -10.5, -45.25, -57);
	CHECK(EquationRoot.roots[0] - 3.6062814044835436 < 0.00001);
	CHECK(EquationRoot.roots[1] - (-4.736243263529858) < 0.00001);
	CHECK(EquationRoot.numRoots == 2);
}

SCENARIO("The discriminants of both equations are less than zero - there are no solutions")
{
	CHECK_THROWS_AS(Solve4(1, 2, 3, 4, 5), std::domain_error);
}
