#pragma once
#include <string>

class Calculator
{
public:
	void DeclareVariable(const std::string& varName);
	void SetVariable(const std::string& varName, const std::string& varValue);
	void DeclareFunction(const std::string& fnName, const std::string& fnValue);
	void Print(const std::string& identifier)const;
	void PrintVars()const;
	void PrintFns()const;

private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
};
