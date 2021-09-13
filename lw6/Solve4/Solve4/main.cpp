#include <iostream>
#include "Solve4.h"
#include <limits>
#include "EquationRoot.h"
#undef max
#undef min

using namespace std;

int main()
{
	double a, b, c, d, e;
	std::string str;
	std::cout << "To solve the equation, enter the 5 coefficients of your fourth-degree equation in the following format: a b c d e\nWarning: the coefficient a must not be equal to 0\n";
	while (!std::cin.eof())
	{
		std::cout << "Coefficients: ";
		try
		{
			std::cin >> a >> b >> c >> d >> e;
			if (std::cin.eof()) break;
			if (std::cin.fail())
			{
				throw std::invalid_argument("Data entered incorrectly");
			}
			EquationRoot4 roots = Solve4(a, b, c, d, e);
			for (size_t i = 0; i < roots.numRoots; i++)
			{
				std::cout << "x" << i+1 << " = " << roots.roots[i] << "\n";
			}
		}
		catch (std::invalid_argument const& e)
		{
			
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			std::cout << "Error: " << e.what() << "\n";
		}
		catch (std::domain_error const& e)
		{
			std::cout << "Error: " << e.what() << "\n";
		}
		catch (...)
		{
			std::cout << "Unknown error\n";
		}
	}
}