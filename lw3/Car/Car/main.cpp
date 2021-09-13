#include <iostream>
#include "CCarControl.h"
#include "CCar.h"

using namespace std;

int main()
{
	CCar car;
	CCarControl control(car, cin, cout);

	cout << "Commands:\n"
		 << "Info\n"
		 << "EngineOn\n"
		 << "EngineOff\n"
		 << "SetGear <gear>\n"
		 << "SetSpeed  <speed>\n";

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!control.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}

	return 0;
}
