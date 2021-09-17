#pragma once
#include <map>
#include <optional>
#include <string>
#include <functional>
#include <vector>
#include <set>

using namespace std;

class Calculator
{
	struct Function
	{
		string leftOperand;
		optional<char> operation;
		optional<string> rightOperand;
	};

public:
	Calculator();
	void DeclareVariable(const string& varName);
	void SetVariable(const string& varName, const string& varValue);
	void DeclareFunction(const string& fnName, const string fnValue);

	const std::map<std::string, double>& GetVars() const;
	const std::map<std::string, double>& GetFns() const;
	optional<double> GetValue(const std::string& identifier) const;

private:
	map<string, double> m_vars;
	map<string, set<string>> m_dependencies;
	map<string, Function> m_fns;
	map<string, double> m_fnValues;

	using Handler = function<double(double, double)>;
	using ActionMap = map<char, Handler>;
	const ActionMap m_actionMap;

	void CheckForDependencies(const string dependencyName);
	void CalculateFunction(string fnName);
	double CalculateSum(const double leftOperand, const double rightOperand) const;
	double CalculateSubtract(const double leftOperand, const double rightOperand) const;
	double CalculateMultiplication(const double leftOperand, const double rightOperand) const;
	double CalculateDivision(const double leftOperand, const double rightOperand) const;

	bool IsVarDeclared(const string varName) const;
	bool IsFnDeclared(const string fnName) const;
	optional<char> FindOperation(const string fnValue) const;
	bool IsIdCorrect(const string& id) const;
};
