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

bool CCar::TurnOnEngine()
{
	m_isTurnedOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (m_speed != 0 || m_gear != 0)
	{
		return false;
	}
	m_isTurnedOn = false;
	return true;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_isTurnedOn)
	{
		throw std::logic_error("It is impossible to change the speed when the engine is turned off");
		return false;
	}
	if (m_gear == 0 && speed > abs(m_speed))
	{
		throw std::logic_error("It is impossible to increase the speed in neutral gear");
		return false;
	}
	if (speed >= CCar::RANGE[m_gear + 1][0] && speed <= RANGE[m_gear + 1][1])
	{
		m_speed = speed;
		if (m_gear == -1)
		{
			m_speed *= -1;
		}
		return true;
	}
	return false;
}

bool CCar::SetGear(int gear)
{
	if (!m_isTurnedOn)
	{ 
		throw std::logic_error("It is impossible to change the gear when the engine is turned off");
		return false;
	}
	if (gear == -1 && m_speed != 0)
	{
		throw std::logic_error("You can only switch to reverse gear at zero speed");
		return false;
	}
	if (gear != 0 && m_gear == -1 && m_speed != 0)
	{
		throw std::logic_error("You can switch from reverse gear only at zero speed");
		return false;
	}
	if (gear != -1 && m_gear == 0 && m_speed < 0)
	{
		throw std::logic_error("After switching from reverse to neutral gear at a non-zero speed, you can only switch to forward gear after stopping");
		return false;
	}
	if (abs(m_speed) >= RANGE[gear + 1][0] && abs(m_speed) <= RANGE[gear + 1][1])
	{
		m_gear = gear;
		return true;
	}
	return false;
}
