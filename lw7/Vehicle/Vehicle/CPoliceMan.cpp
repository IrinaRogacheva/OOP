#include "CPoliceMan.h"

CPoliceMan::CPoliceMan(const std::string& name, const std::string& departmentName)
	: CPersonImpl(name)
	, m_departmentName(departmentName)
{
}

std::string CPoliceMan::GetDepartmentName() const
{
	return std::string(m_departmentName);
}
