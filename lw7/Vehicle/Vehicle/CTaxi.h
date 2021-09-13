#pragma once
#include "CCarImpl.h"
#include "ITaxi.h"

class CTaxi : public CCarImpl<ITaxi, IPerson>
{
public:
	CTaxi(size_t placeCount, MakeOfTheCar MakeOfTheCar);
};
