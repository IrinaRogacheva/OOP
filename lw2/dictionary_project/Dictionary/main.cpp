#include <windows.h>
#include "Dictionary.h"

string GetDictionaryFileName(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw invalid_argument("Invalid arguments count. Usage: MiniDictionary.exe <dictionary file name>");
	}
	return argv[1];
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string fileName;
	try
	{
		fileName = GetDictionaryFileName(argc, argv);
	}
	catch (exception e)
	{
		cout << e.what() << endl;
		return 1;
	}
	
	ifstream inputDictionaryFile(fileName);
	map<string, string> dictionary = ReadDictFile(inputDictionaryFile);
	BilingualDictionary bilingualDictionary = { ReadDictFile(inputDictionaryFile), GenerateReverseDictionary(dictionary) };
	size_t initialSizeOfDictionary = dictionary.size();

	ProcessUserInput(bilingualDictionary);

	if (bilingualDictionary.dictionary.size() > initialSizeOfDictionary)
	{
		CheckSavingOfChangesInDictionary(dictionary, fileName);
	}
}
