#include "Calculator.h"
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

Calculator::Calculator()
	: m_actionMap({
		{ '+', [this](const double leftOperand, const double rightOperand) {
			 return CalculateSum(leftOperand, rightOperand);
		 } },
		{ '-', [this](const double leftOperand, const double rightOperand) {
			 return CalculateSubtract(leftOperand, rightOperand);
		 } },
		{ '*', [this](const double leftOperand, const double rightOperand) {
			 return CalculateMultiplication(leftOperand, rightOperand);
		 } },
		{ '/', [this](const double leftOperand, const double rightOperand) {
			 return CalculateDivision(leftOperand, rightOperand);
		 } },
	})
{
}

void Calculator::DeclareVariable(const string& varName)
{
	if (IsVarDeclared(varName) || IsFnDeclared(varName))
	{
		throw invalid_argument("The identifier matches one of the previously declared ones");
	}
	if (!IsIdCorrect(varName))
	{
		throw invalid_argument("The identifier can consist of letters, numbers, and an underscore character and can't start with a digit");
	}
	m_vars[varName] = numeric_limits<double>::quiet_NaN();
}

void Calculator::SetVariable(const string& varName, const string& varValue)
{
	if (IsFnDeclared(varName))
	{
		throw invalid_argument("The variable name must not match the name of the declared function");
	}
	if (!IsIdCorrect(varName))
	{
		throw invalid_argument("The identifier can consist of letters, numbers, and an underscore character and can't start with a digit");
	}

	optional<double> previousValue;
	if (GetValue(varName))
	{
		previousValue = *(GetValue(varName));
	}
	try
	{
		m_vars[varName] = stod(varValue);
	}
	catch (std::invalid_argument)
	{
		if (IsVarDeclared(varValue))
		{
			m_vars[varName] = m_vars[varValue];
		}
		else if (IsFnDeclared(varValue))
		{
			m_vars[varName] = m_fnValues[varValue];
		}
		else
		{
			throw invalid_argument("A variable named \"" + varValue + "\" is not declared");
		}
	}

	try
	{
		CheckForDependencies(varName);
	}
	catch (const exception&)
	{
		m_vars[varName] = *(previousValue);
		throw;
	}
}

void Calculator::DeclareFunction(const string& fnName, const string fnValue)
{
	if (IsVarDeclared(fnName) || IsFnDeclared(fnName))
	{
		throw invalid_argument("The identifier matches one of the previously declared ones");
	}
	if (!IsIdCorrect(fnName))
	{
		throw invalid_argument("The identifier can consist of letters, numbers, and an underscore character and can't start with a digit");
	}

	string leftOperand, rightOperand;
	Function resultFunction;
	if (FindOperation(fnValue))
	{
		char operation = *(FindOperation(fnValue));
		leftOperand = fnValue.substr(0, fnValue.find(operation));
		rightOperand = fnValue.substr(fnValue.find(operation) + 1);

		if (!IsVarDeclared(rightOperand) && !IsFnDeclared(rightOperand))
		{
			throw invalid_argument("A variable named \"" + rightOperand + "\" is not declared");
		}
		resultFunction = { leftOperand, operation, rightOperand };
	}
	else
	{
		leftOperand = fnValue;
		resultFunction = { leftOperand, nullopt, nullopt };
	}

	if (!IsVarDeclared(leftOperand) && !IsFnDeclared(leftOperand))
	{
		throw invalid_argument("A variable named \"" + leftOperand + "\" is not declared");
	}

	try
	{
		if (FindOperation(fnValue))
		{
			m_dependencies[rightOperand].insert(fnName);
		}
		m_dependencies[leftOperand].insert(fnName);
		m_fns[fnName] = resultFunction;
		CalculateFunction(fnName);
	}
	catch (const exception&)
	{
		m_fns.erase(fnName);
		m_dependencies.erase(rightOperand);
		m_dependencies.erase(leftOperand);
		throw;
	}
}

void Calculator::CheckForDependencies(const string dependencyName)
{
	if (m_dependencies.find(dependencyName) != m_dependencies.end())
	{
		for (string functionName : m_dependencies[dependencyName])
		{
			CalculateFunction(functionName);
		}
	}
}

void Calculator::CalculateFunction(const string fnName)
{
	Function function = m_fns[fnName];
	if (function.operation)
	{
		try
		{
			auto it = m_actionMap.find(*(function.operation));
			m_fnValues[fnName] = it->second(*(GetValue(function.leftOperand)), *(GetValue(*(function.rightOperand))));
		}
		catch (const exception&)
		{
			throw;
		}
	}
	else
	{
		m_fnValues[fnName] = *(GetValue(function.leftOperand));
	}

	CheckForDependencies(fnName);
}

double Calculator::CalculateSum(const double leftOperand, const double rightOperand) const
{
	return leftOperand + rightOperand;
}

double Calculator::CalculateSubtract(const double leftOperand, const double rightOperand) const
{
	return leftOperand - rightOperand;
}

double Calculator::CalculateMultiplication(const double leftOperand, const double rightOperand) const
{
	return leftOperand * rightOperand;
}

double Calculator::CalculateDivision(const double leftOperand, const double rightOperand) const
{
	if (rightOperand == 0)
	{
		throw invalid_argument("Division by 0");
	}
	return leftOperand / rightOperand;
}

bool Calculator::IsVarDeclared(const string varName) const
{
	return m_vars.find(varName) != m_vars.end();
}

bool Calculator::IsFnDeclared(const string fnName) const
{
	return m_fns.find(fnName) != m_fns.end();
}

optional<char> Calculator::FindOperation(const string fnValue) const
{
	for (auto& var : m_actionMap)
	{
		if (fnValue.find(var.first) != string::npos)
		{
			return var.first;
		}
	}
	return nullopt;
}

const map<string, double>& Calculator::GetVars() const
{
	return m_vars;
}

const map<string, double>& Calculator::GetFns() const
{
	return m_fnValues;
}

optional<double> Calculator::GetValue(const string& identifier) const
{
	if (IsVarDeclared(identifier))
	{
		return m_vars.at(identifier);
	}

	if (IsFnDeclared(identifier))
	{
		return m_fnValues.at(identifier);
	}

	return nullopt;
}

bool Calculator::IsIdCorrect(const string& id) const
{
	if (id.empty() || isdigit(id[0]) || !all_of(id.begin(), id.end(), [](char ch) { return isalnum(ch) || ch == '_'; }))
	{
		return false;
	}

	return true;
}