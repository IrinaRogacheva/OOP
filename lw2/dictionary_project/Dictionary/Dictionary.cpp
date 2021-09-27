#include "Dictionary.h"
#include <algorithm>
#include <sstream>

void AddReverseTranslation(map<string, string>& reverseDictionary, const string& key, const string& value)
{
	if (reverseDictionary.find(value) != reverseDictionary.end() && reverseDictionary[value].find(key) == string::npos)
	{
		reverseDictionary[value] = reverseDictionary[value].append(",").append(key);
	}
	else
	{
		reverseDictionary.emplace(value, key);
	}
}

map<string, string> GenerateReverseDictionary(const map<string, string>& dictionary)
{
	map<string, string> reverseDictionary;
	string value;
	for (auto& item : dictionary)
	{
		std::stringstream iss(item.second);
		while (getline(iss, value, ','))
		{
			AddReverseTranslation(reverseDictionary, item.first, value);
		}
	}
	return reverseDictionary;
}

map<string, string> ReadDictFile(ifstream& dictFile)
{
	map<string, string> dictionary;
	if (dictFile.is_open())
	{
		string str;
		size_t pos;
		while (getline(dictFile, str))
		{
			pos = str.find("|");
			dictionary.emplace(str.substr(0, pos), str.substr(pos + 1, str.size()));
		}
	}
	return dictionary;
}

void CheckSavingOfWord(BilingualDictionary& bilingualDictionary, const string& newWord)
{
	cout << "Неизвестное слово \"" << newWord << "\". Введите перевод или пустую строку для отказа." << endl << ">";
	string translate;
	getline(cin, translate);
	if (translate != "")
	{
		bilingualDictionary.dictionary.emplace(newWord, translate);
		AddReverseTranslation(bilingualDictionary.reverseDictionary, newWord, translate);
		cout << "Слово \"" << newWord << "\" сохранено в словаре как \"" << translate << "\"." << endl;
	}
	else
	{
		cout << "Слово \"" << newWord << "\" проигнорировано." << endl;
	}
}

void WriteTranslate(const string& inputStr, BilingualDictionary& bilingualDictionary)
{
	if (bilingualDictionary.dictionary.find(inputStr) != bilingualDictionary.dictionary.end() && bilingualDictionary.reverseDictionary.find(inputStr) != bilingualDictionary.reverseDictionary.end())
	{
		cout << bilingualDictionary.dictionary[inputStr] << "," << bilingualDictionary.reverseDictionary[inputStr] << endl;
	}
	else if (bilingualDictionary.dictionary.find(inputStr) != bilingualDictionary.dictionary.end())
	{
		cout << bilingualDictionary.dictionary[inputStr] << endl;
	}
	else if (bilingualDictionary.reverseDictionary.find(inputStr) != bilingualDictionary.reverseDictionary.end())
	{
		cout << bilingualDictionary.reverseDictionary[inputStr] << endl;
	}
	else
	{
		CheckSavingOfWord(bilingualDictionary, inputStr);
	}
}

void ProcessUserInput(BilingualDictionary& bilingualDictionary)
{
	string inputStr;
	cout << "Введите слово, которое хотите перевести. Для выхода введите многоточие \"...\"" << endl;
	while (inputStr != "...")
	{
		cout << ">";
		getline(cin, inputStr);

		if (inputStr == "...")
		{
			break;
		}

		transform(inputStr.begin(), inputStr.end(), inputStr.begin(), tolower);
		WriteTranslate(inputStr, bilingualDictionary);
	}
}

void SaveChangesToFile(const map<string, string>& dictionary, const string& fileName)
{
	ofstream outputDictionaryFile(fileName);
	for (auto& item : dictionary)
	{
		outputDictionaryFile << item.first << "|" << item.second << endl;
	}
}

void CheckSavingOfChangesInDictionary(const map<string, string>& dictionary, const string& fileName)
{
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl << ">";
	string str;
	getline(cin, str);
	if (str == "Y" || str == "y")
	{
		SaveChangesToFile(dictionary, fileName);
		cout << "Изменения сохранены. До свидания." << endl;
	}
	else
	{
		cout << "Изменения не были сохранены. До свидания." << endl;
	}
}
