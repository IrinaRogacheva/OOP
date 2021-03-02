#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include "Radix.h"

int CheckRadix(const std::string& str, bool& wasError)
{
	std::string checkedString;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			checkedString += str[i];
		}
		else
		{
			wasError = true;
		}
	}
	int radix = std::stoi(checkedString);
	if (radix < 2 || radix > 36)
	{
		wasError = true;
	}
	return std::stoi(checkedString);
}

struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: Radix.exe <source notation> <destination notation> <value>\n";
		return std::nullopt;
	}
	Args args;
	bool wasError = false;
	args.sourceNotation = CheckRadix(argv[1], wasError);
	args.destinationNotation = CheckRadix(argv[2], wasError);
	if (wasError)
	{
		std::cout << "Invalid radix argument\n";
		std::cout << "Radix must be a number from 2 to 32\n";
		return std::nullopt;
	}
	args.value = argv[3];
	return args;
}

std::string fillKeyString()
{
	std::string str(47, '\0'); //Инициализация строки длиной 46 символов (кол-во допустимых символов) нулями
	for (int i = 0; i < 10; i ++)
	{
		str[i] = (char)(i + 48); //Заполнение строки цифрами от 0 до 9 (коды 48-58)
	}
	for (int i = 10; i < str.size(); i++)
	{
		str[i] = (char)(i + 55); //Заполнение строки буквами 'A'-'Z' (коды 65-90)
	}
	str[str.size()] = '-';
	return str;
}

struct Error
{
	bool wasError;
	std::string message;
};

int StringToInt(const std::string& str, const std::string& keyStr, int radix, Error& err)
{
	int result = 0;
	bool overflow = false;
	int degree = str.size() - 1;
	double copyDegree = degree;
	double inverseDegree;
	for (char ch : str)
	{
		if (keyStr.find(ch) != -1 && keyStr.find(ch) <= radix)
		{
			int dif = INT_MAX - result;
			if (degree != 0)
			{
				copyDegree = (double)degree;
				inverseDegree = 1 / copyDegree;
				overflow = pow((INT_MAX - result) / keyStr.find(ch), inverseDegree) <= radix;
			}
			if (!overflow)
			{
				result += keyStr.find(ch) * pow(radix, degree);
				degree--;
			}
			else
			{
				err.wasError = true;
				err.message = "Overflow\n" "Too large argument <value>";	
			}
		}
		else
		{
			err.wasError = true;
			err.message = "Invalid value argument\n" "Value can not contain characters that do not belong to radix " + radix;	
		}
	}
	return result;
}

std::string IntToString(int n, const std::string& keyStr, int radix, bool& wasError)
{
	int count = n;
	std::string str;
	while (count > 0)
	{
		n = count % radix;
		count = count / radix;
		str = keyStr[n] + str;
	}
	return str;
}

int main(int argc, char* argv[])
{
	bool wasError = false;
	auto args = ParseArgs(argc, argv);
	//Проверка правильности аргументов командной строки
	if (!args)
	{
		return 1;
	}

	std::string keyString = fillKeyString();

	Error err;
	int decInt = StringToInt(args->value, keyString, args->sourceNotation, err);
	if (err.wasError)
	{
		std::cout << err.message << "\n";
		return 1;
	}
	std::cout << decInt << "\n";
	if (args->destinationNotation != 10)
	{
		std::cout << IntToString(decInt, keyString, args->destinationNotation, wasError);
	}

	return 0;
}
