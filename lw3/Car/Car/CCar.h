#pragma once

//перенести в файл .cpp
#include "const.h"
#include "Direction.h"

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

private:
	int m_gear;
	bool m_isTurnedOn;
	int m_speed;
};