#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Calculator/Calculator.h"
#include "../Calculator/CommandControl.h"

#include <chrono>

using namespace std;

TEST_CASE("Initialization of a list of valid commands in the CommandControl class")
{
	GIVEN("Correct command names given")
	{
		vector<string> validCommandNames{ "var", "let", "printvars", "fn", "print", "printfns" };

		WHEN("Calculator and menu classes created")
		{
			Calculator calculator;
			stringstream input, output;
			CommandControl commandControl(calculator, input, output);

			WHEN("Invalid command name is used")
			{
				THEN("Error message is displayed")
				{
					input.clear();
					input << "begin";
					commandControl.HandleCommand();

					REQUIRE(output.str() == "Unknown command!\n");
				}
			}
		}
	}
}

TEST_CASE("Declaring variables and displaying")
{
	GIVEN("Class Calculator and CommandControl announced")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);

		WHEN("When we initialize a new variable with the correct name")
		{
			THEN("Added variable with initial nan value")
			{
				input << "var x";
				commandControl.HandleCommand();
				input.clear();

				auto mapVar = calculator.GetVars();
				map<string, double>::iterator it;

				it = mapVar.find("x");
				REQUIRE(it != mapVar.end());
				REQUIRE(isnan(mapVar["x"]));

				AND_WHEN("Try to add variable with the same name")
				{
					THEN("Error message is displayed")
					{
						input << "var x";
						commandControl.HandleCommand();
						input.clear();

						REQUIRE(output.str() == "The identifier matches one of the previously declared ones\n");
					}
				}
			}

			AND_THEN("Underscore in variable name")
			{
				input.clear();
				input << "var x_abs";
				commandControl.HandleCommand();

				auto mapVar = calculator.GetVars();
				map<string, double>::iterator it;

				it = mapVar.find("x_abs");
				REQUIRE(it != mapVar.end());
				REQUIRE(isnan(mapVar["x_abs"]));
			}

			AND_WHEN("Invalid variable name: first character is a digit")
			{
				THEN("Error message is displayed")
				{
					input.clear();
					input << "var 7abc";
					commandControl.HandleCommand();
					REQUIRE(output.str() == "The identifier can consist of letters, numbers, and an underscore character and can't start with a digit\n");
				}
			}

			AND_WHEN("Invalid variable name: forbidden character")
			{
				THEN("Error message is displayed")
				{
					input.clear();
					input << "var a$c";
					commandControl.HandleCommand();
					REQUIRE(output.str() == "The identifier can consist of letters, numbers, and an underscore character and can't start with a digit\n");
				}
			}
		}
	}
}

TEST_CASE("Assignment to a variable")
{
	GIVEN("Class calculator, menu and initialize a new variable")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);
		input << "var x";
		commandControl.HandleCommand();

		WHEN("Assign a numerical value to the variable")
		{
			THEN("The value of this given variable changes")
			{
				input.clear();
				input << "let x=3.14";
				commandControl.HandleCommand();

				auto mapVar = calculator.GetVars();
				map<string, double>::iterator it;

				it = mapVar.find("x");

				REQUIRE(it != mapVar.end());
				REQUIRE(!isnan(mapVar["x"]));
				REQUIRE(mapVar["x"] == 3.14);
			}

			AND_WHEN("Assign a numeric value to an undeclared variable")
			{
				THEN("The value of this given variable changes")
				{
					input.clear();
					input << "let y=2.277";
					commandControl.HandleCommand();

					auto mapVar = calculator.GetVars();
					map<string, double>::iterator it;

					it = mapVar.find("y");

					REQUIRE(it != mapVar.end());
					REQUIRE(!isnan(mapVar["y"]));
					REQUIRE(mapVar["y"] == 2.277);
				}
			}

			AND_WHEN("Reassigning a variable to another variable")
			{
				THEN("The value of this given variable changes")
				{
					input.clear();
					input << "let x=3.14";
					commandControl.HandleCommand();

					input.clear();
					input << "let y=x";
					commandControl.HandleCommand();

					auto mapVar = calculator.GetVars();
					map<string, double>::iterator it;

					it = mapVar.find("y");

					REQUIRE(it != mapVar.end());
					REQUIRE(!isnan(mapVar["y"]));
					REQUIRE(mapVar["y"] == 3.14);
				}
			}

			AND_WHEN("Attempt to assign a value to an undeclared variable")
			{
				THEN("Error is displayed: Unrecognized variable")
				{
					input.clear();
					input << "let x=z";
					commandControl.HandleCommand();
					REQUIRE(output.str() == "A variable named \"z\" is not declared\n");
				}
			}

			AND_WHEN("Invalid expression assignment")
			{
				THEN("Error is displayed: Invalid name of varible")
				{
					input.clear();
					input << "let x= ";
					commandControl.HandleCommand();

					REQUIRE(output.str() == "A variable named \"\" is not declared\n");
				}
			}
		}
	}
}

TEST_CASE("Display of variables and their values")
{
	GIVEN("Calculator class, menu and variable initialization with value")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);
		vector<string> startingCommand{ "var x", "let y=2.2333" };

		for (auto& command : startingCommand)
		{
			input << command;
			commandControl.HandleCommand();
			input.clear();
		}

		WHEN("The printvars command will display all declared variables and their values")
		{
			THEN("Output of variables and their values")
			{
				input << "printvars";
				commandControl.HandleCommand();

				REQUIRE(output.str() == "x:nan\ny:2.23\n");
			}
		}

		AND_WHEN("enter the print <identifier> command")
		{
			THEN("The value of the variable or function specified by the print command is displayed")
			{
				input << "print y";
				commandControl.HandleCommand();

				REQUIRE(output.str() == "2.23\n");
				input.clear();
			}

			AND_THEN("The value of the variable or function specified by the print command is displayed")
			{
				input << "print x";
				commandControl.HandleCommand();

				REQUIRE(output.str() == "nan\n");
				input.clear();
			}
		}
	}
}

TEST_CASE("Function declaration")
{
	GIVEN("Calculator class, menu and variables")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);
		vector<string> startingCommand{ "var x", "var y" };

		for (auto& command : startingCommand)
		{
			input << command;
			commandControl.HandleCommand();
			input.clear();
		}

		WHEN("Declare a function and assign it the result of applying one of the following binary operations")
		{
			THEN("The value of the function will be nan")
			{
				input << "fn XplusY=x+y";
				commandControl.HandleCommand();
				input.clear();
				REQUIRE(isnan(*(calculator.GetValue("XplusY"))));

				input << "print XplusY";
				commandControl.HandleCommand();

				REQUIRE(output.str() == "nan\n");
			}

			AND_WHEN("Variables are initialized")
			{
				vector<string> commandLine{ "let x=3", "let y=4", "fn XplusY=x+y", "print XplusY" };

				THEN("In the function, the result of applying binary operations is written.")
				{
					for (auto& command : commandLine)
					{
						input << command;
						commandControl.HandleCommand();
						input.clear();
					}

					REQUIRE(!isnan(*(calculator.GetValue("XplusY"))));
					REQUIRE(output.str() == "7.00\n");
				}
			}

			AND_WHEN("Assign a value to a function")
			{
				vector<string> commandLine{ "let x=3.1415", "fn funX=x", "print funX" };

				THEN("The value of the function is equal to the value of the variable")
				{
					for (auto& command : commandLine)
					{
						input << command;
						commandControl.HandleCommand();
						input.clear();
					}

					REQUIRE(output.str() == "3.14\n");
					REQUIRE(calculator.GetValue("funX") == calculator.GetValue("x"));
				}
			}

			AND_WHEN("Variable was not declared")
			{
				THEN("Error message is displayed")
				{
					input << "fn XplusY=x+Z";
					commandControl.HandleCommand();
					input.clear();

					REQUIRE(!calculator.GetValue("XplusY"));
					REQUIRE(output.str() == "A variable named \"Z\" is not declared\n");
				}
			}

			AND_WHEN("Function name is a variable")
			{
				THEN("Error message is displayed")
				{
					input << "fn x=y";
					commandControl.HandleCommand();
					input.clear();

					REQUIRE(output.str() == "The identifier matches one of the previously declared ones\n");
				}
			}

			AND_WHEN("Invalid character encountered in assignment iterator")
			{
				THEN("Error message is displayed")
				{
					input << "fn XplusY=x%y";
					commandControl.HandleCommand();
					input.clear();

					REQUIRE(output.str() == "A variable named \"x%y\" is not declared\n");
				}
			}
		}
	}
}

TEST_CASE("Declaring a division function when the divisor is 0")
{
	GIVEN("Calculator class, menu, and list of commands")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);
		vector<string> commandLine{ "let x=5",
			"let y=0",
			"fn XDivideY=x/y",
			"print XDivideY" };

		WHEN("When trying to execute these commands an error message is displayed")
		{
			for (size_t i = 0; i < commandLine.size(); ++i)
			{
				input << commandLine[i];
				commandControl.HandleCommand();
				input.clear();
			}

			REQUIRE(output.str() == "Division by 0\nAn identifier named \"XDivideY\" is not declared\n");

			THEN("The XDivideY function was not added to the list of functions")
			{
				REQUIRE(calculator.GetFns().find("XDivideY") == calculator.GetFns().end());
			}
		}
	}
}

TEST_CASE("Set the divisible value of one of the functions to zero")
{
	GIVEN("Calculator class, menu, and list of commands")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);
		vector<string> commandLine{ "var x",
			"var y",
			"fn XDivideY=x/y",
			"let y=0",
			"print y" };

		WHEN("When trying to execute these commands an error message is displayed")
		{
			for (size_t i = 0; i < commandLine.size(); ++i)
			{
				input << commandLine[i];
				commandControl.HandleCommand();
				input.clear();
			}

			REQUIRE(output.str() == "Division by 0\nnan\n");
		}
	}
}

TEST_CASE("Circle area calculation")
{
	GIVEN("Calculator class, menu, and list of commands")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);
		vector<string> commandLine{ "var radius",
			"let pi=3.14159265",
			"fn radiusSquared=radius*radius",
			"fn circleArea=pi*radiusSquared",
			"let radius=10",
			"let circle10Area=circleArea",
			"let radius=20",
			"let circle20Area=circleArea" };

		WHEN("Stepwise calculation of the area of a circle")
		{
			for (size_t i = 0; i < commandLine.size(); ++i)
			{
				input << commandLine[i];
				commandControl.HandleCommand();
				input.clear();
			}

			THEN("The following statements will be true")
			{
				REQUIRE(calculator.GetValue("pi") == 3.14159265);
				REQUIRE(calculator.GetValue("radius") == 20);
				REQUIRE(calculator.GetValue("radiusSquared") == 400);
				REQUIRE(calculator.GetValue("circleArea") == 1256.63706);
				REQUIRE(calculator.GetValue("circle10Area") == 314.159265);
				REQUIRE(calculator.GetValue("circle20Area") == calculator.GetValue("circleArea"));
			}

			AND_THEN("Print all functions")
			{
				input << "printfns";
				commandControl.HandleCommand();
				input.clear();

				REQUIRE(output.str() == "circleArea:1256.64\nradiusSquared:400.00\n");
			}

			AND_THEN("Print all variables")
			{
				input << "printvars";
				commandControl.HandleCommand();
				input.clear();

				REQUIRE(output.str() == "circle10Area:314.16\ncircle20Area:1256.64\npi:3.14\nradius:20.00\n");
			}
		}
	}
}

TEST_CASE("The Fibonacci sequence calculation")
{
	GIVEN("Calculator class, menu, and list of commands")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);
		vector<string> commandLine{ "let v0=0",
			"let v1=1",
			"fn fib0=v0",
			"fn fib1=v1",
			"fn fib2=fib1+fib0",
			"fn fib3=fib2+fib1",
			"fn fib4=fib3+fib2",
			"fn fib5=fib4+fib3",
			"fn fib6=fib5+fib4" };

		WHEN("Stepwise calculation of the Fibonacci sequence")
		{
			for (size_t i = 0; i < commandLine.size(); ++i)
			{
				input << commandLine[i];
				commandControl.HandleCommand();
				input.clear();
			}

			THEN("Print all functions")
			{
				input << "printfns";
				commandControl.HandleCommand();
				input.clear();

				REQUIRE(output.str() == "fib0:0.00\nfib1:1.00\nfib2:1.00\nfib3:2.00\nfib4:3.00\nfib5:5.00\nfib6:8.00\n");
			}

			AND_THEN("Change the value of variable v0 and print functions")
			{
				input << "let v0=1";
				commandControl.HandleCommand();
				input.clear();

				input << "printfns";
				commandControl.HandleCommand();
				input.clear();

				REQUIRE(output.str() == "fib0:1.00\nfib1:1.00\nfib2:2.00\nfib3:3.00\nfib4:5.00\nfib5:8.00\nfib6:13.00\n");
			}
		}
	}
}

TEST_CASE("An attempt to calculate the value of the 50th number of the Fibonacci sequence")
{
	GIVEN("Calculator class, menu, and list of commands")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);
		vector<string> commandLine{ "let v0=0",
			"let v1=1",
			"fn fib0=v0",
			"fn fib1=v1" };

		string command;
		for (size_t i = 2; i <= 25; i++)
		{
			command = "fn fib" + std::to_string(i) + "=fib" + std::to_string(i - 1) + "+fib" + std::to_string(i - 2);
			commandLine.push_back(command);
		}

		WHEN("Stepwise calculation of the Fibonacci sequence")
		{
			for (size_t i = 0; i < commandLine.size(); ++i)
			{
				input << commandLine[i];
				commandControl.HandleCommand();
				input.clear();
			}

			chrono::steady_clock sc;
			input << "let v0=1";
			auto start = sc.now();
			commandControl.HandleCommand();
			auto end = sc.now();

			auto time_span = static_cast<chrono::duration<double>>(end - start);
			input.clear();
			output << time_span.count() << " seconds !!!";

				REQUIRE(output.str() == "fib0:0.00\n");
		}
	}
}

TEST_CASE("calculating very large sequences of functions")
{
	GIVEN("Calculator class, menu, and list of commands")
	{
		Calculator calculator;
		stringstream input, output;
		CommandControl commandControl(calculator, input, output);
		vector<string> commandLine{ "let x=1",
			"fn x2=x+x" };

		string command;
		for (size_t i = 3; i <= 1000000; i++)
		{
			command = "fn x" + std::to_string(i) + "=x" + std::to_string(i - 1) + "+x";
			commandLine.push_back(command);
		}

		WHEN("Stepwise calculation of the Fibonacci sequence")
		{
			for (size_t i = 0; i < commandLine.size(); ++i)
			{
				input << commandLine[i];
				commandControl.HandleCommand();
				input.clear();
			}

			chrono::steady_clock sc;
			input << "let x=2";
			auto start = sc.now();
			commandControl.HandleCommand();
			auto end = sc.now();

			auto time_span = static_cast<chrono::duration<double>>(end - start);
			input.clear();
			output << time_span.count() << " seconds !!!";

			REQUIRE(output.str() == "fib0:0.00\n");
		}
	}
}
