#pragma once

#include <array>

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

const std::array<std::array<int, 2>, 7> RANGE
{
	{ { 0, 20 },
		{ 0, INT_MAX },
		{ 0, 30 },
		{ 20, 50 },
		{ 30, 60 },
		{ 40, 90 },
		{ 50, 150 } }
};
