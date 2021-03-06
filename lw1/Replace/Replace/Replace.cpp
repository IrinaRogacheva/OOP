﻿#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include "Replace.h"

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: Replace.exe <input file> <output file> <search string> <replace string>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

std::string ReplaceSubstring(const std::string& str, const std::string& searchString, const std::string& replaceString)
{
	size_t pos = 0;
	std::string resultString;
	if (searchString != "")
	{
		size_t nextPos = str.find(searchString);
		while (nextPos != std::string::npos)
		{
			resultString.append(str, pos, nextPos - pos).append(replaceString);
			pos = nextPos + searchString.size();
			nextPos = str.find(searchString, pos);
		}
	}
	resultString.append(str, pos);
	return resultString;
}

void CopyReplacedString(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replaceString)
{
	//Поиск и замена подстроки во входном файле с записью в выходной
	std::string str;
	std::string resultString = str;
	while (getline(input, str))
	{
		str = ReplaceSubstring(str, searchString, replaceString);
		output << str << "\n";
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	//Проверка правильности аргументов командной строки
	if (!args)
	{
		return 1;
	}

	//Открываем входной файл
	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
		return 1;
	}

	//Открываем выходной файл
	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << args->outputFileName << "' for writing\n";
		return 1;
	}

	CopyReplacedString(input, output, args->searchString, args->replaceString);

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return 1;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return 1;
	}

	return 0;
}
