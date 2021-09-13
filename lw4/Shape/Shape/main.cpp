#include "CShapeControl.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	CCar car;
	CCarControl control(car, cin, cout);

	cout << "Commands:\n"
		 << "\tInfo\n"
		 << "\tEngineOn\n"
		 << "\tEngineOff\n"
		 << "\tSetGear <gear>\n"
		 << "\tSetSpeep <speed>\n";

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