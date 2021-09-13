#include "CommandControl.h"
#include "Calculator.h"
#include <sstream>
#include <iomanip>

using namespace std;
using namespace std::placeholders;

CommandControl::CommandControl(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "var", bind(&CommandControl::DeclareVariable, this, std::placeholders::_1) },
		  { "let", bind(&CommandControl::SetVariable, this, std::placeholders::_1) },
		  { "fn", bind(&CommandControl::DeclareFunction, this, std::placeholders::_1) },
		  { "print", bind(&CommandControl::Print, this, std::placeholders::_1) },
		  { "printvars", bind(&CommandControl::PrintVars, this, std::placeholders::_1) },
		  { "printfns", bind(&CommandControl::PrintFns, this, std::placeholders::_1) },
	  })
{
}

void CommandControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
	}
	else
	{
		m_output << "Unknown command!\n";
	}
}

void CommandControl::DeclareVariable(std::istream& args)
{
	try
	{
		string varName;
		args >> varName;
		m_calculator.DeclareVariable(varName);
	}
	catch (const exception& e)
	{
		m_output << e.what() << endl;
	}
}

void CommandControl::SetVariable(std::istream& args)
{
	try
	{
		string expression;
		args >> expression;
		size_t pos = expression.find("=");
		m_calculator.SetVariable(expression.substr(0, pos), expression.substr(pos + 1));
	}
	catch (const exception& e)
	{
		m_output << e.what() << endl;
	}
}

void CommandControl::DeclareFunction(std::istream& args)
{
	try
	{
		string expression;
		args >> expression;
		size_t pos = expression.find("=");
		m_calculator.DeclareFunction(expression.substr(0, pos), expression.substr(pos + 1));
	}
	catch (const exception& e)
	{
		m_output << e.what() << endl;
	}
}

void CommandControl::Print(std::istream& args)
{
	string identifier;
	args >> identifier;
	
	if (!m_calculator.GetValue(identifier))
	{
		m_output << "An identifier named \"" << identifier << "\" is not declared" << endl;
	}
	else
	{
		m_output << std::fixed;
		m_output << setprecision(2) << *(m_calculator.GetValue(identifier)) << endl;
	}
}

void CommandControl::PrintVars(std::istream& /*args*/)
{
	m_output << fixed << setprecision(2);
	for (auto& var : m_calculator.GetVars())
	{
		m_output << var.first << ":" << var.second << endl;
	}
}

void CommandControl::PrintFns(std::istream& /*args*/)
{
	m_output << fixed << setprecision(2);
	for (auto& fnValue : m_calculator.GetFns())
	{
		m_output << fnValue.first << ":" << fnValue.second << endl;
	}
}
