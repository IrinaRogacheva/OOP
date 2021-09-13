#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

#include "../CMyArray/CMyArray.h"

SCENARIO("Creating empty array templated by double")
{
	CMyArray<double> array;
	REQUIRE(array.GetSize() == 0);
	REQUIRE(array.GetCapacity() == 0);
	REQUIRE_THROWS(array[0]);

	WHEN("Push value")
	{
		REQUIRE_NOTHROW(array.Push(1.1));

		THEN("Size and capacity of array become 1 and value is at zero position")
		{
			REQUIRE(array.GetSize() == 1);
			REQUIRE(array.GetCapacity() == 1);
			REQUIRE(array[0] == 1.1);
		}

		AND_WHEN("Try to acces to index out of range")
		{
			THEN("Exception out of range")
			{
				REQUIRE_THROWS(array[1]);
			}
		}
	}

	WHEN("Add many values to array")
	{
		REQUIRE_NOTHROW(array.Push(2.2));
		REQUIRE_NOTHROW(array.Push(3.3));
		REQUIRE_NOTHROW(array.Push(4.4));
		REQUIRE_NOTHROW(array.Push(5.5));

		AND_WHEN("Resize array to 10")
		{
			REQUIRE_NOTHROW(array.Resize(10));

			THEN("Size of array is 10 and value at size position is 0")
			{
				REQUIRE(array.GetSize() == 10);
				REQUIRE(array[5] == 0);
			}
		}

		AND_WHEN("Resize array to 2")
		{
			REQUIRE_NOTHROW(array.Resize(2));

			THEN("Size of array is 2")
			{
				REQUIRE(array.GetSize() == 2);
				
			}

			AND_WHEN("Try to acces to index out of range")
			{
				THEN("Exception out of range")
				{
					REQUIRE_THROWS(array[2]);
				}
			}
		}

		AND_WHEN("Clear array")
		{
			REQUIRE_NOTHROW(array.Clear());

			THEN("Empty array")
			{
				REQUIRE(array.GetSize() == 0);
				REQUIRE(array.GetCapacity() == 0);
				REQUIRE_THROWS(array[0]);
			}
		}
	}
}


SCENARIO("Creating empty array templated by string")
{
	CMyArray<std::string> array;
	REQUIRE(array.GetSize() == 0);
	REQUIRE(array.GetCapacity() == 0);
	REQUIRE_THROWS(array[0]);

	WHEN("Push value")
	{
		REQUIRE_NOTHROW(array.Push("first string"));

		THEN("Size and capacity of array become 1 and value is at zero position")
		{
			REQUIRE(array.GetSize() == 1);
			REQUIRE(array.GetCapacity() == 1);
			REQUIRE(array[0] == "first string");
		}

		AND_WHEN("Try to acces to index out of range")
		{
			THEN("Exception out of range")
			{
				REQUIRE_THROWS(array[1]);
			}
		}
	}

	WHEN("Add many values to array")
	{
		REQUIRE_NOTHROW(array.Push("second string"));
		REQUIRE_NOTHROW(array.Push("third string"));
		REQUIRE_NOTHROW(array.Push("fourth string"));
		REQUIRE_NOTHROW(array.Push("fifth string"));

		AND_WHEN("Resize array to 10")
		{
			REQUIRE_NOTHROW(array.Resize(10));

			THEN("Size of array is 10 and value at size position is empty string")
			{
				REQUIRE(array.GetSize() == 10);
				REQUIRE(array[5] == "");
			}
		}

		AND_WHEN("Resize array to 2")
		{
			REQUIRE_NOTHROW(array.Resize(2));

			THEN("Size of array is 2")
			{
				REQUIRE(array.GetSize() == 2);
			}
		}

		AND_WHEN("Clear array")
		{
			REQUIRE_NOTHROW(array.Clear());

			THEN("Empty array")
			{
				REQUIRE(array.GetSize() == 0);
				REQUIRE(array.GetCapacity() == 0);
				REQUIRE_THROWS(array[0]);
			}
		}
	}
}


SCENARIO("Copying array and moving to other var")
{
	GIVEN("Array with three elements")
	{
		CMyArray<double> array;
		REQUIRE_NOTHROW(array.Push(1.1));
		REQUIRE_NOTHROW(array.Push(2.2));
		REQUIRE_NOTHROW(array.Push(3.3));

		WHEN("We copy array to another by sending to constructor")
		{
			bool wasError = false;
			try
			{
				CMyArray<double> excellentCopy(array);
				THEN("Make copy of the array")
				{
					for (size_t i = 0; i < array.GetSize(); i++)
					{
						REQUIRE(excellentCopy[i] == array[i]);
					}
				}
			}
			catch (...)
			{
				wasError = true;
			}

			REQUIRE_FALSE(wasError);
		}

		WHEN("Assign array to other arr")
		{
			CMyArray<double> excellentCopy;
			REQUIRE_NOTHROW(excellentCopy = array);

			THEN("Got copy of array")
			{
				for (size_t i = 0; i < array.GetSize(); i++)
				{
					REQUIRE(excellentCopy[i] == array[i]);
				}

				AND_WHEN("Change some value in array")
				{
					array[2] = 4.0;

					THEN("Value at same index in copy not changed")
					{
						REQUIRE_FALSE(array[2] == excellentCopy[2]);
						REQUIRE(excellentCopy[2] == 3.3);
					}
				}
			}
		}

		WHEN("Move array to arr in constructor")
		{
			CMyArray<double> arr = std::move(array);

			THEN("We got array without content and dest with array data")
			{
				REQUIRE(array.GetSize() == 0);
				REQUIRE(arr.GetSize() == 3);
			}
		}

		WHEN("Move array to arr by assign operator")
		{
			CMyArray<double> arr;
			REQUIRE(arr.GetSize() == 0);
			arr = std::move(array);

			THEN("Got array without content and arr with array data")
			{
				REQUIRE(array.GetSize() == 0);
				REQUIRE(arr.GetSize() == 3);
			}
		}
	}
}

SCENARIO("Iterate array forward and backward")
{
	GIVEN("Array with few elements")
	{
		CMyArray<double> array;

		REQUIRE_NOTHROW(array.Push(1.1));
		REQUIRE_NOTHROW(array.Push(2.2));
		REQUIRE_NOTHROW(array.Push(3.3));

		WHEN("Iterate array forward")
		{
			THEN("Got elements in direct order")
			{
				int i = 0;
				for (auto it = array.begin(); it != array.end(); it++, i++)
				{
					REQUIRE(*it == array[i]);
				}
			}
		}

		WHEN("Iterate array backward")
		{
			THEN("Got elements in reverse order")
			{
				size_t i = array.GetSize() - 1;
				for (auto it = array.rbegin(); it != array.rend(); it++, i--)
				{
					REQUIRE(*it == array[i]);
				}
			}
		}
	}
}
