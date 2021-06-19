#include "CMyArray.h"
#include <iostream>
#include <string>
#include "windows.h"

template <class T>
void PrintArray(const CMyArray<T>& array)
{
	std::cout << "Direct order" << std::endl;
	for (auto it = array.begin(); it != array.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	std::cout << "Reverse order" << std::endl;
	for (auto it = array.rbegin(); it != array.rend(); it++)
	{
		std::cout << *it << std::endl;
	}
}

int main()
{
	CMyArray<double> doubleArray;
	doubleArray.Push(1.1);
	doubleArray.Push(2.2);
	doubleArray.Push(3.3);
	doubleArray.Push(4.4);
	PrintArray(doubleArray);
	
	CMyArray<std::string> stringArray;
	stringArray.Push("1 string");
	stringArray.Push("2 string");
	stringArray.Push("3 string");
	stringArray.Push("4 string");
	PrintArray(stringArray);

	return 0;
}
