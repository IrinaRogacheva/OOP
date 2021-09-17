#include "CCarControl.h"
#include "CCar.h"
#include <sstream>

using namespace std;
using namespace std::placeholders;

CCarControl::CCarControl(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "Info", bind(&CCarControl::Info, this, _1) },
		{ "EngineOn", bind(&CCarControl::TurnEngineOn, this, _1) },
		{ "EngineOff", bind(&CCarControl::TurnEngineOff, this, _1) },
		{ "SetGear", bind(&CCarControl::SetGear, this, _1) },
		{ "SetSpeed", bind(&CCarControl::SetSpeed, this, _1) },
	  })
{
}

bool CCarControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CCarControl::TurnEngineOn(std::istream& /*args*/)
{
	m_car.TurnOnEngine();
	m_output << "Engine is turned on\n";
	return true;
}

bool CCarControl::TurnEngineOff(std::istream& /*args*/)
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine is turned off\n";
	}
	else
	{
		m_output << "To turn off the engine, there must be a neutral gear, and speed = 0\n";
	}

	return true;
}

bool CCarControl::SetGear(std::istream& args)
{
	int gear;
	args >> gear;
	if (args.fail() || gear < CCar::MIN_GEAR || gear > CCar::MAX_GEAR)
	{
		m_output << "Invalid argument. The gear must be an integer from -1 to 5\n";
		return false;
	}
	try
	{
		m_car.SetGear(gear);
		m_output << "The gear was switched successfully\n";
		return true;
	}
	catch (std::exception& e)
	{
		m_output << e.what() << std::endl;
		return false;
	}
	return true;
}

bool CCarControl::SetSpeed(std::istream& args)
{
	int speed;
	args >> speed;
	if (args.fail() || speed < 0)
	{
		m_output << "Incorrect input. The speed must be an integer more than zero\n";
		return false;
	}
	try
	{
		m_car.SetSpeed(speed);
		m_output << "Speed was changed successfully\n";
		return true;
	}
	catch(std::exception &e)
	{
		m_output << e.what() << std::endl;
		return false;
	}
} 

bool CCarControl::Info(std::istream& /*args*/) const
{
	string directionString = m_car.GetDirection() == Direction::STAND 
		? "stand" 
		: (m_car.GetDirection() == Direction::FORWARD ? "forward" : "backward");
	m_output << "Engine: " << (m_car.IsTurnedOn() ? "is turned on" : "is turned off") << endl;
	m_output << "Direction: " << directionString << endl;
	m_output << "Speed: " << m_car.GetSpeed() << endl;
	m_output << "Gear: " << m_car.GetGear() << endl;

	return true;
}