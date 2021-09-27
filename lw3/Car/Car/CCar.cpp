#include "CCar.h"
#include <stdexcept>
#include <iostream>

CCar::CCar()
	: m_speed(0)
	, m_isTurnedOn(false)
	, m_gear(0)
{
}

bool CCar::IsTurnedOn() const
{
	return m_isTurnedOn;
}

int CCar::GetSpeed() const
{
	return abs(m_speed);
}

int CCar::GetGear() const
{
	return m_gear;
}

Direction CCar::GetDirection() const
{
	Direction direction = m_speed == 0 
		? Direction::STAND 
		: (m_speed < 0 ? Direction::BACKWARD : Direction::FORWARD);
	return direction;
}

void CCar::TurnOnEngine()
{
	m_isTurnedOn = true;
}

void CCar::TurnOffEngine()
{
	if (m_speed != 0 || m_gear != 0)
	{
		throw std::logic_error("To turn off the engine, there must be a neutral gear, and speed = 0");
	}
	m_isTurnedOn = false;
}

void CCar::SetSpeed(int speed)
{
	if (speed < 0)
	{
		throw std::logic_error("The speed must be greater than or equal to zero");
	}
	if (!m_isTurnedOn)
	{
		throw std::logic_error("It is impossible to change the speed when the engine is turned off");
	}
	if (m_gear == 0 && speed > abs(m_speed))
	{
		throw std::logic_error("It is impossible to increase the speed in neutral gear");
	}
	bool isBackward = (GetDirection() == Direction::BACKWARD);
	if (speed >= CCar::RANGE[m_gear + 1][0] && speed <= RANGE[m_gear + 1][1])
	{
		m_speed = speed;
		if (isBackward || m_gear == -1)//
		{
			m_speed *= -1;
		}
	}
	else
	{
		throw std::logic_error("You can't set this speed in the current gear of the car");
	}
}

void CCar::SetGear(int gear)
{
	if (gear < CCar::MIN_GEAR || gear > CCar::MAX_GEAR)
	{
		throw std::logic_error("The gear can take values from -1 to 5");
	}
	if (!m_isTurnedOn)
	{ 
		throw std::logic_error("It is impossible to change the gear when the engine is turned off");
	}
	if (gear == -1 && m_speed != 0)
	{
		throw std::logic_error("You can only switch to reverse gear at zero speed");
	}
	if (gear != 0 && m_gear == -1 && m_speed != 0)
	{
		throw std::logic_error("You can switch from reverse gear only at zero speed");
	}
	if (gear != -1 && m_gear == 0 && m_speed < 0)
	{
		throw std::logic_error("After switching from reverse to neutral gear at a non-zero speed, you can only switch to forward gear after stopping");
	}
	if (abs(m_speed) >= RANGE[gear + 1][0] && abs(m_speed) <= RANGE[gear + 1][1])
	{
		m_gear = gear;
	}
	else
	{
		throw std::logic_error("You can't switch to this gear at the current speed of the car");
	}
}
