#pragma once
#include "CVehicleImpl.h"
#include "MakeOfTheCar.h"

template <typename Base, typename Passenger>
class CCarImpl : public CVehicleImpl<Base, Passenger>
{
public:
	CCarImpl(size_t placeCount, MakeOfTheCar makeOfTheCar)
		: CVehicleImpl<Base, Passenger>(placeCount)
		, m_makeOfTheCar(makeOfTheCar){};

	MakeOfTheCar GetMakeOfTheCar() const
	{
		return m_makeOfTheCar;
	};

private:
	const MakeOfTheCar m_makeOfTheCar;
};
