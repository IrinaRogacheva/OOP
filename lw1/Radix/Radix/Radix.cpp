#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include "Radix.h"

const std::string KEY_STRING = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int StrToInt(std::string s)
{
	int n = 0;
	for (int i = 0; s[i] >= '0' && s[i] <= '9'; i++)
		n = 10 * n + (s[i] - '0');
	return n;
}

int CheckRadix(const std::string& radixStr, bool& wasError)
{
	std::string checkedString;
	for (size_t i = 0; i < radixStr.size(); i++)
	{
		if (radixStr[i] >= '0' && radixStr[i] <= '9')
		{
			checkedString += radixStr[i];
		}
		else
		{
			wasError = true;
		}
	}	
	int radix = StrToInt(checkedString);
	if (radix < 2 || radix > 36)
	{
		wasError = true;
	}
	return radix;
}

void CheckValue(const std::string& value, unsigned int radix, bool& wasError, bool& isNegative)
{
	size_t key;
	for (size_t i = 0; i < value.size(); i++)
	{
		if (value[0] == '-')
		{
			isNegative = true;
			continue;
		}
		key = KEY_STRING.find(value[i]);
		if (key == std::string::npos || key > radix)
		{
			wasError = true;
		}
	}
}

struct Args
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[], bool& isNegative)
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
		std::cout << "Radix must be a number from 2 to 36\n";
		return std::nullopt;
	}
	CheckValue(argv[3], args.sourceNotation, wasError, isNegative);
	if (wasError)
	{
		std::cout << "Invalid value argument\n";
		std::cout << "Value can not contain characters that do not belong to radix " << args.sourceNotation << "\n ";
		return std::nullopt;
	}
	args.value = argv[3];
	return args;
}

int StringToInt(const std::string& str, unsigned int radix, bool& wasError, bool isNegative)
{
	int result = 0;
	bool overflow = false;
	int degree = str.size() - 1;
	double copyDegree = (double)degree;
	double inverseDegree = 1 / copyDegree;
	size_t key;
	for (char ch : str)
	{
		if (!isNegative)
		{
			key = KEY_STRING.find(ch);
			if (degree != 0 && key != 0)
			{
				copyDegree = (double)degree;
				inverseDegree = 1 / copyDegree;
				overflow = pow((INT_MAX - result) / key, inverseDegree) <= radix;
			}
			if (!overflow)
			{
				result += static_cast<int>(key * pow(radix, degree));
			}
			else
			{
				wasError = true;
			}
		}
		degree--;
	}
	if (isNegative)
	{
		result *= -1;
	}
	return result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	bool isNegative = false;
	if (n < 0)
	{
		isNegative = true;
		n *= -1;
	}
	int count = n;
	std::string str;
	while (count > 0)
	{
		n = count % radix;
		count = count / radix;
		str = KEY_STRING[n] + str;
	}
	if (isNegative)
	{
		str.insert(0, "-");
	}
	return str;
}

int main(int argc, char* argv[])
{
	bool wasError = false;
	bool isNegative = false;
	auto args = ParseArgs(argc, argv, isNegative);
	//Проверка правильности аргументов командной строки
	if (!args)
	{
		return 1;
	}
	int decInt = StringToInt(args->value, args->sourceNotation, wasError, isNegative);
	if (wasError)
	{
		std::cout << "Overflow\n" << "Too large argument <value>\n";
		return 1;
	}
	//std::cout << "Dec Int: " << decInt << "\n";
	std::cout << IntToString(decInt, args->destinationNotation, wasError);

	return 0;
}
