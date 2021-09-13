#pragma once
#include "CCar.h"
#include <sstream>
#include <functional>
#include <vector>
#include <map>

class CCarControl
{
public:
	CCarControl(CCar &car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool TurnEngineOn(std::istream&);
	bool TurnEngineOff(std::istream&);
	bool SetGear(std::istream&);
	bool SetSpeed(std::istream&);
	bool Info(std::istream&) const;

private:
	typedef std::function<bool(std::istream& args)> Handler;
	typedef std::map<std::string, Handler> ActionMap;

	std::istream& m_input;
	std::ostream& m_output;

	CCar& m_car;

	const ActionMap m_actionMap;
};