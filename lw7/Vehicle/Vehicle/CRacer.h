#pragma once
#include "CPersonImpl.h"
#include "IRacer.h"

class CRacer : public CPersonImpl<IRacer>
{
public:
	CRacer(const std::string& name, size_t awardsCount);

	size_t GetAwardsCount() const;

private:
	size_t m_awardsCount;
};
