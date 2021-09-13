#pragma once
#include "CCarImpl.h"
#include "IRacingCar.h"

class CRacingCar : public CCarImpl<IRacingCar, IRacer>
{
public:
	CRacingCar(size_t placeCount, MakeOfTheCar carModel);
};
