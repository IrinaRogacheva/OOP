#pragma once
#include <string>

template <typename Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl(const std::string& name)
		: m_name(name){};

	~CPersonImpl() = default;

	std::string GetName() const
	{
		return std::string(m_name);
	};

private:
	std::string m_name;
};
