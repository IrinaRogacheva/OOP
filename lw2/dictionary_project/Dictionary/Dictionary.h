#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

struct BilingualDictionary
{
	map<string, string> dictionary;
	map<string, string> reverseDictionary;
};

map<string, string> ReadDictFile(ifstream& dictFile);

map<string, string> GenerateReverseDictionary(const map<string, string>& dictionary);

void CheckSavingOfWord(BilingualDictionary& bilingualDictionary, const string& newWord);

void ProcessUserInput(BilingualDictionary& bilingualDictionary);

void CheckSavingOfChangesInDictionary(const map<string, string>& dictionary, const string& fileName);

void WriteTranslate(const string& inputStr, BilingualDictionary& bilingualDictionary);