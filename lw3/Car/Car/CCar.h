#pragma once

#include "Direction.h"
#include <array>

class CCar
{
public:
	CCar();
	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

	static constexpr const std::array<std::array<int, 2>, 7> RANGE{
		{ { 0, 20 },
			{ 0, INT_MAX },
			{ 0, 30 },
			{ 20, 50 },
			{ 30, 60 },
			{ 40, 90 },
			{ 50, 150 } }
	};
	static const int MIN_GEAR = -1;
	static const int MAX_GEAR = 5;

private:
	int m_gear;
	bool m_isTurnedOn;
	int m_speed;
};