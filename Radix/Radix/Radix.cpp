#include <fstream>
#include <iostream>
#include <optional>
#include <string>

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
	if (radix < 2 || radix > 32)
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

std::optional<Args> ParseArgs(int argc, char* argv[], bool& wasError)
{
	if (argc != 4)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: Radix.exe <source notation> <destination notation> <value>\n";
		return std::nullopt;
	}
	Args args;
	args.sourceNotation = CheckRadix(argv[1], wasError);
	args.destinationNotation = CheckRadix(argv[2], wasError);
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

int StringToInt(const std::string& str, const std::string& keyStr, int radix, bool& wasError)
{
	int result = 0;
	bool overflow = false;
	int count = str.size() - 1;
	for (char ch : str)
	{
		if (keyStr.find(ch) != -1)
		{
			if (--count != 0)
			{
				overflow = pow((INT_MAX - result) / keyStr.find(ch), 1/count) <= radix;
			}
			if (!overflow)
			{
				result += keyStr.find(ch) * pow(radix, count);
			}
			else
			{
				wasError = true;
				std::cout << "Error" << "\n";
			}
		}
		else
		{
			wasError = true;
			std::cout << "Error 1" << "\n";
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
	auto args = ParseArgs(argc, argv, wasError);
	if (wasError)
	{
		std::cout << "Invalid radix argument\n";
		std::cout << "Radix must be a number from 2 to 32\n";
		return 1;
	}
	//Проверка правильности аргументов командной строки
	if (!args)
	{
		return 1;
	}

	std::string keyString = fillKeyString();

	int decInt = StringToInt(args->value, keyString, args->sourceNotation, wasError);
	if (wasError)
	{
		std::cout << "Invalid value argument\n";
		std::cout << "Value can not contain characters that do not belong to radix " << args->sourceNotation << "\n";
		return 1;
	}

	std::cout << IntToString(decInt, keyString, args->destinationNotation, wasError);

	return 0;
}
