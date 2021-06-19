#include "CTVSet.h"
#include <iostream>

bool CTVSet::IsTurnedOn() const
{
	return m_isOn;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

int CTVSet::GetChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

bool CTVSet::SelectChannel(int channel)
{
	bool isAvailableChannel = (channel >= 1) && (channel <= 99);
	if (isAvailableChannel && m_isOn)
	{
		m_selectedChannel = channel;
		return true;
	}
	return false;
}

void CTVSet::Info() const
{
	std::string curState;
	m_isOn ? curState = "Включен" : curState = "Выключен";
	std::cout << "Текущее состояние телевизора:" << "\n" << curState << "\n";
	std::cout << "Номер выбранного канала: " << m_selectedChannel << "\n";
}