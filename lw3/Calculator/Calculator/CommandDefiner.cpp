#include "CommandDefiner.h"
#include "Calculator.h"

using namespace std;
using namespace std::placeholders;

CommandDefiner::CommandDefiner(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "var", bind(&CommandDefiner::DeclareVariable, this, std::placeholders::_1) },
		{ "let", bind(&CommandDefiner::SetVariable, this, std::placeholders::_1) },
		{ "fn", bind(&CommandDefiner::DeclareFunction, this, std::placeholders::_1) },
		{ "print", bind(&CommandDefiner::Print, this, std::placeholders::_1) },
		{ "printvars", bind(&CommandDefiner::PrintVars, this, std::placeholders::_1) },
		{ "printfns", bind(&CommandDefiner::PrintFns, this, std::placeholders::_1) },
	  })
{
}

bool CommandDefiner::DefineCommand()
{
	return false;
}

bool CommandDefiner::DeclareVariable(std::istream& /*args*/)
{
	return false;
}

bool CommandDefiner::SetVariable(std::istream& /*args*/)
{
	return false;
}

bool CommandDefiner::DeclareFunction(std::istream& /*args*/)
{
	return false;
}

bool CommandDefiner::Print(std::istream& /*args*/)
{
	return false;
}

bool CommandDefiner::PrintVars()
{
	return false;
}

bool CommandDefiner::PrintFns()
{
	return false;
}
