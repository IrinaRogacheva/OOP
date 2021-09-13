#include "CPerson.h"
#include "CPoliceCar.h"
#include "CPoliceMan.h"
#include "CRacer.h"
#include "CTaxi.h"
#include <iostream>

int main()
{
	CPoliceCar policeCar(5, MakeOfTheCar::FORD);
	auto pJohnSmith = std::make_shared<CPoliceMan>("John Smith", "North-West Police Station");
	policeCar.AddPassenger(pJohnSmith);

	auto pJimClark = std::make_shared<CPoliceMan>("Jim Clark", "South-East Police Station");
	policeCar.AddPassenger(pJimClark);

	std::cout << policeCar.GetPassenger(0).GetName() << std::endl;
	std::cout << policeCar.GetPassenger(0).GetDepartmentName() << std::endl;
	std::cout << policeCar.GetPassenger(1).GetName() << std::endl;
	std::cout << policeCar.GetPassenger(1).GetDepartmentName() << std::endl;

	policeCar.RemovePassenger(1);

	CTaxi taxi(2, MakeOfTheCar::TOYOTA);
	auto pRajaGandhi = std::make_shared<CPerson>("Raja Gandhi");
	auto pMichaelSchumacher = std::make_shared<CRacer>("Michael Schumacher", 91);
	taxi.AddPassenger(pRajaGandhi);
	taxi.AddPassenger(pMichaelSchumacher);

	taxi.RemovePassenger(0);
	taxi.AddPassenger(pJimClark);

	try
	{
		taxi.AddPassenger(pRajaGandhi);
	}
	catch (const std::logic_error& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
