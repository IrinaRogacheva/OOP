#pragma once
#include <string>

class IPerson
{
public:
	virtual ~IPerson() = default;

	virtual std::string GetName() const = 0;
};
