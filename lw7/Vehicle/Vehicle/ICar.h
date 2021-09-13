#pragma once
#include "IVehicle.h"
#include "MakeOfTheCar.h"

template <typename Passenger>
class ICar : public IVehicle<Passenger>
{
public:
	virtual MakeOfTheCar GetMakeOfTheCar() const = 0;
};
