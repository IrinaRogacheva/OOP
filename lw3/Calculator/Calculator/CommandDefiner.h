#pragma once
#include <string>
#include <functional>
#include <map>

class Calculator;

class CommandDefiner
{
public:
	CommandDefiner(Calculator& calculator, std::istream& input, std::ostream& output);
	bool DefineCommand();

private:
	bool DeclareVariable(std::istream& args);
	bool SetVariable(std::istream& args);
	bool DeclareFunction(std::istream& args);
	bool Print(std::istream& args);
	bool PrintVars();
	bool PrintFns();

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
