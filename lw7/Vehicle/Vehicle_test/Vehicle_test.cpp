#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../Vehicle/CTaxi.h"
#include "../Vehicle/CPerson.h"
#include "../Vehicle/CPoliceMan.h"
#include "../Vehicle/CRacer.h"


SCENARIO("Creating taxi")
{
	CTaxi taxiCar(3, MakeOfTheCar::BMW);
	REQUIRE(taxiCar.GetMakeOfTheCar() == MakeOfTheCar::BMW);
	REQUIRE(taxiCar.IsEmpty());
	REQUIRE(taxiCar.GetPlaceCount() == 3);
	REQUIRE_THROWS(taxiCar.GetPassenger(0));
	auto person = std::make_shared<CPerson>("John");
	REQUIRE_NOTHROW(taxiCar.AddPassenger(person));
	WHEN("Passenger was added")
	{
		THEN("The number of passengers increased by one and we can get the passenger's name")
		{
			REQUIRE(taxiCar.GetPassengerCount() == 1);
			REQUIRE(taxiCar.GetPassenger(0).GetName() == "John");
		}
		AND_WHEN("Add two more passengers: a police man and a racer")
		{
			auto policman = std::make_shared<CPoliceMan>("Dan Espinoza", "L.A. Police Station");
			REQUIRE_NOTHROW(taxiCar.AddPassenger(policman));

			auto racer = std::make_shared<CRacer>("Sebastian Vettel", 50);
			REQUIRE_NOTHROW(taxiCar.AddPassenger(racer));

			THEN("The taxi is full and an exception will be thrown when trying to add another passenger")
			{
				REQUIRE(taxiCar.IsFull());
				auto otherPerson = std::make_shared<CPerson>("Jane");
				REQUIRE_THROWS(taxiCar.AddPassenger(otherPerson));
			}

			AND_WHEN("Delete passenger policeman")
			{
				taxiCar.RemovePassenger(1);
				THEN("The number of passengers decreased by one")
				{
					REQUIRE(taxiCar.GetPassengerCount() == 2);
				}
				AND_WHEN("Try to remove a passenger by a non-existent index and remove all passengers")
				{
					REQUIRE_THROWS(taxiCar.RemovePassenger(2));
					taxiCar.RemoveAllPassengers();
					THEN("The taxi is empty")
					{
						REQUIRE(taxiCar.IsEmpty());
					}
				}
			}
		}
	}
}

