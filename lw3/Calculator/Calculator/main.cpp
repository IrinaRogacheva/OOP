#include "Calculator.h"
#include "CommandControl.h"
#include <iostream>

using namespace std;

int main()
{
	Calculator calculator;
	CommandControl commandControl(calculator, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		commandControl.HandleCommand();
	}

	return 0;
}
