#pragma once
#include "CCarImpl.h"
#include "IPoliceCar.h"

class CPoliceCar : public CCarImpl<IPoliceCar, IPoliceMan>
{
public:
	CPoliceCar(size_t placeCount, MakeOfTheCar MakeOfTheCar);
};
