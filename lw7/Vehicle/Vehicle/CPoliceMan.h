#pragma once
#include "CPersonImpl.h"
#include "IPoliceMan.h"

class CPoliceMan : public CPersonImpl<IPoliceMan>
{
public:
	CPoliceMan(const std::string& name, const std::string& departmentName);

	std::string GetDepartmentName() const;

private:
	std::string m_departmentName;
};
