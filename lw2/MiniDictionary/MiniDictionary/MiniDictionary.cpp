
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <map>
#include <algorithm>
#include <Windows.h>
#include "Dictionary.h"

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
        cout << "Usage: MiniDicrionary.exe <output file name>\n";
        return nullopt;
    }
    Args args;
    args.fileName = argv[1];

    return args;
}

int main(int argc, char* argv[])
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    map<string, string> dictionary = LoadDictionary(args->fileName);
    size_t sizeMap = dictionary.size();
    string englWord;
    while (getline(cin, englWord))
    {
        std::transform(englWord.begin(), englWord.end(), englWord.begin(), std::tolower);
        if (englWord == "...")
        {
            CheckChangesAndFinishWork(sizeMap, dictionary, args->fileName);
            break;
        }
        WriteTranslation(dictionary, englWord);
    }
    return 0;
}