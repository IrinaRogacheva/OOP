#pragma once
#include "CPersonImpl.h"
#include "IPerson.h"

class CPerson : public CPersonImpl<IPerson>
{
public:
	CPerson(const std::string& name);
};
