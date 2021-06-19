#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <map>
#include <optional>
#include <algorithm>

using namespace std;

struct Args
{
	string fileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: MiniDictionary.exe <dictionary file name>\n";
		return nullopt;
	}
	Args args;
	args.fileName = argv[1];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	ifstream dictFile(args->fileName);
	string inputStr;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	do
	{
		cout << "Введите слово на английском языке. Для выхода введите многоточие \"...\"" << "\n";
		getline(cin, inputStr);
		if (IsDictFileExists(dictFile))
		{
			if (!ReadDictFile(dictFile))
			{
				return 1;
			}
			else
			{
				map<string, string> dictionary = ReadDictFile(dictFile);
			}
			if (FindWord(inputStr))
			{
			}
			else
			{
			}
		}
		else
		{
		}
	} while (inputStr != "...");
}

bool IsDictFileExists(const ifstream& dictFile)
{
	return dictFile.is_open();
}

optional<map<string, string>> ReadDictFile(ifstream& dictFile)
{
	map<string, string> dictionary;
	string str;
	while (getline(dictFile, str))
	{
		if (count(str.begin(), str.end(), '"') != 4 || str.find('"') != 0 || str.rfind('"') != str.size())
		{
			cout << "Invalid format of dictionary file" << "\n";
			cout << "Usage: \"word\" \"translation\"\n";
			return nullopt;
		}
		size_t quotePos = str.find('"');
		size_t nextQuotePos = str.find('"', 1);
		string key;
		key = str.substr(quotePos, nextQuotePos - quotePos);
		dictionary.emplace(key, str.substr(quotePos, nextQuotePos - quotePos));
	}
	return dictionary;
}

optional<string> FindWord(string str)
{

}
