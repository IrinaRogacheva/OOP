#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Car/CCar.h"
#include "../Car/CCarControl.h"

SCENARIO("Create the car object and turn on the engine")
{
	CCar car;
	REQUIRE(car.IsTurnedOn() == false);
	REQUIRE(car.GetDirection() == Direction::STAND);
	REQUIRE(car.GetGear() == 0);
	REQUIRE(car.GetSpeed() == 0);
	WHEN("By default")
	{
		THEN("It is impossible to change the gear and speed")
		{
			REQUIRE_THROWS_AS(car.SetSpeed(20), std::logic_error);
			REQUIRE_THROWS_AS(car.SetGear(1), std::logic_error);
		}
	}
}

SCENARIO("Turn on the engine and try to switch from neutral gear to other gears")
{
	CCar car; 
	THEN("The car's engine is switched on")
	{
		car.TurnOnEngine();
		REQUIRE(car.IsTurnedOn() == true);
		REQUIRE(car.GetDirection() == Direction::STAND);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);
		WHEN("The car is in neutral gear")
		{
			THEN("It is impossible to increase the speed")
			{
				REQUIRE_THROWS_AS(car.SetSpeed(10), std::logic_error);
			}
			AND_THEN("It is possible to switch to reverse gear")
			{
				REQUIRE_NOTHROW(car.SetGear(-1));
				REQUIRE(car.GetGear() == -1);
				REQUIRE(car.GetDirection() == Direction::STAND);
				AND_THEN("Change speed and switch to neutral gear")
				{
					car.SetSpeed(20);
					REQUIRE(car.GetDirection() == Direction::BACKWARD);
					car.SetGear(0);
					car.SetSpeed(19);
					WHEN("Direction of the car must be backward")
					{
						REQUIRE(car.GetDirection() == Direction::BACKWARD);
					}
				}
			}
			AND_THEN("It is possible to switch to the first gear")
			{
				REQUIRE_NOTHROW(car.SetGear(1));
				REQUIRE(car.GetGear() == 1);
				REQUIRE(car.GetDirection() == Direction::STAND);
			}
			AND_THEN("It is impossible to switch to the second gear")
			{
				REQUIRE_THROWS_AS(car.SetGear(2), std::logic_error);
				REQUIRE(car.GetGear() == 0);
				REQUIRE(car.GetDirection() == Direction::STAND);
			}
		}
	}
}

SCENARIO("Switch the first gear and then the second")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	REQUIRE(car.GetGear() == 1);
	REQUIRE_NOTHROW(car.SetSpeed(20));
	REQUIRE(car.GetSpeed() == 20);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
	THEN("It is possible to switch to the second gear")
	{
		REQUIRE_NOTHROW(car.SetGear(2));
		REQUIRE(car.GetGear() == 2);
		REQUIRE(car.GetDirection() == Direction::FORWARD);
		WHEN("Increase the speed to 30")
		{
			REQUIRE_NOTHROW(car.SetSpeed(30));
			THEN("It is possible to switch to the third gear")
			{
				REQUIRE_NOTHROW(car.SetGear(3));
				REQUIRE(car.GetGear() == 3);
				REQUIRE(car.GetDirection() == Direction::FORWARD);
			}
		}
		AND_WHEN("Try to increase the speed to 51")
		{
			THEN("It is impossible to increase the speed to 51")
			{
				REQUIRE_THROWS_AS(car.SetSpeed(51), std::logic_error);
			}
		}
	}
}

SCENARIO("Try to switch to the reverse gear and back")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	WHEN("The speed of the car is not zero")
	{
		car.SetSpeed(15);
		THEN("It is impossible to switch to reverse gear")
		{
			REQUIRE_THROWS_AS(car.SetGear(-1), std::logic_error);
		}
	}
	AND_WHEN("The speed of the car is zero")
	{
		REQUIRE(car.GetSpeed() == 0);
		THEN("It is possible to switch to the reverse gear")
		{
			REQUIRE_NOTHROW(car.SetGear(-1));
			REQUIRE(car.GetDirection() == Direction::STAND);
			WHEN("Change the speed of the car")
			{
				REQUIRE_NOTHROW(car.SetSpeed(20));
				REQUIRE(car.GetDirection() == Direction::BACKWARD);
				THEN("It is impossible to switch to the first gear")
				{
					REQUIRE_THROWS_AS(car.SetGear(1), std::logic_error);
				}
				WHEN("Switch to the neutral gear")
				{
					THEN("It is impossible to switch to forward gear")
					{
						REQUIRE_THROWS_AS(car.SetGear(1), std::logic_error);
					}
					AND_WHEN("Stop the car")
					{
						car.SetSpeed(0);
						THEN("It is possible to switch to forward gear")
						{
							REQUIRE_NOTHROW(car.SetGear(1));
						}
					}
				}
			}
			AND_WHEN("It is possible to switch to the first gear")
			{
				REQUIRE_NOTHROW(car.SetGear(1));
			}
		}
	}
}

SCENARIO("Try to turn off the engine")
{
	CCar car;
	car.TurnOnEngine();
	WHEN("The car is in the first gear")
	{
		car.SetGear(1);
		THEN("It is impossible to turn off the engiine")
		{
			REQUIRE_THROWS_AS(car.TurnOffEngine(), std::logic_error);
		}
		WHEN("Increase the speed of the car and switch the gear to neutral")
		{
			car.SetSpeed(20);
			car.SetGear(0);
			THEN("It is impossible to turn off the engiine")
			{
				REQUIRE_THROWS_AS(car.TurnOffEngine(), std::logic_error);
			}
			WHEN("Reduce the speed of the car to zero") 
			{
				car.SetSpeed(0);
				THEN("It is possible to turn off the engine")
				{
					REQUIRE_NOTHROW(car.TurnOffEngine());
				}
			}
		}
	}
}

SCENARIO("Turn on and turn off the engine using CCarControl")
{
	CCar car;
	std::stringstream input, output;
	CCarControl control(car, input, output);

	WHEN("Input command to turn on the engine")
	{
		input << "EngineOn";
		REQUIRE(control.HandleCommand() == true);
		input.clear();
		THEN("Output a message that the engine is turned on")
		{
			std::string expectedOutput = std::string("Engine is turned on\n");
			REQUIRE(output.str() == expectedOutput);
		}
		WHEN("Input command to turn off the engine")
		{		
			output.str("");
			input << "EngineOff";
			REQUIRE(control.HandleCommand() == true);
			input.clear();

			THEN("Output a message that the engine is turned off")
			{
				std::string expectedOutput = std::string("Engine is turned off\n");
				REQUIRE(output.str() == expectedOutput);
				output.clear();
			}
		}
	}
}

SCENARIO("Change the gear and the speed of the car using CCarControl")
{
	CCar car;
	std::stringstream input, output;
	CCarControl control(car, input, output);
    
	input << "EngineOn";
	control.HandleCommand();
	input.clear();
	output.str("");
	WHEN("Input command to change the gear")
	{
		input << "SetGear 1";
		REQUIRE(control.HandleCommand() == true);
		input.clear();
		THEN("Output a message that the gear is switched")
		{
			std::string expectedOutput = std::string("The gear was switched successfully\n");
			REQUIRE(output.str() == expectedOutput);
			output.str("");
			WHEN("Try to turn off the engine")
			{
				input << "EngineOff";
				control.HandleCommand();
				std::string expectedOutput = std::string("To turn off the engine, there must be a neutral gear, and speed = 0\n");
				REQUIRE(output.str() == expectedOutput);
			}
		}
	}
}

SCENARIO("Input incorrect parameter in commands")
{
	CCar car;
	std::stringstream input, output;
	CCarControl control(car, input, output);
	input << "EngineOn";
	control.HandleCommand();
	input.clear();
	output.str("");
	WHEN("Input command to change the gear with incorrect parameter")
	{
		input << "SetGear reg";
		control.HandleCommand();
		THEN("Output a message about incorrect input")
		{
			std::string expectedOutput = std::string("Invalid argument. The gear must be an integer from -1 to 5\n");
			REQUIRE(output.str() == expectedOutput);
			output.str("");
		}
	}
	AND_WHEN("Input command to change the speed with incorrect parameter")
	{
		input << "SetSpeed -4";
		control.HandleCommand();
		THEN("Output a message about incorrect input")
		{
			std::string expectedOutput = std::string("The speed must be greater than or equal to zero\n");
			REQUIRE(output.str() == expectedOutput);
			output.str("");
		}
	}
}
