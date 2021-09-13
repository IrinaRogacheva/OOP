#pragma once
#include <istream>
#include <functional>
#include <map>

class Calculator;

class CommandControl
{
public:
	CommandControl(Calculator& tv, std::istream& input, std::ostream& output);
	void HandleCommand();
private:
	void DeclareVariable(std::istream& args);
	void SetVariable(std::istream& args);
	void DeclareFunction(std::istream& args);
	void Print(std::istream& args);
	void PrintVars(std::istream& args);
	void PrintFns(std::istream& args);

private:
	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	const ActionMap m_actionMap;

	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;
};
