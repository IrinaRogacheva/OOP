#include <iostream>
#include "Calculator.h"
#include "CommandDefiner.h"

using namespace std;

int main()
{
	Calculator calculator;
	CommandDefiner defineCommand(calculator, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!defineCommand.DefineCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}
