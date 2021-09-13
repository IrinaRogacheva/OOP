// MiniDistionary_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <map>
#include "../../catch2/catch.hpp"
#include "../MiniDictionary/Dictionary.h"

SCENARIO("fill map")
{
	WHEN("input file is empty")
	{
		std::string fileName = "Empty.txt";
		THEN("map is empty too")
		{
			std::map<std::string, std::string> dict = {};
			CHECK(FillMap(fileName) == dict);
		}

	}

	WHEN("input file contains word list where first arguments is 1 word")
	{
		std::string fileName = "OneWord.txt";
		THEN("key is first word, value is remaining words")
		{
			std::map<std::string, std::string> dict = { {"dog", "собака, пес"}, {"room", "комната"} };
			CHECK(FillMap(fileName) == dict);
		}
	}

	WHEN("input file contains word list where first arguments is few words")
	{
		std::string fileName = "FewWords.txt";
		THEN("key is words to first double space, value is remaining words")
		{
			std::map<std::string, std::string> dict = { {"the red square", "крассная площадь"} };
			CHECK(FillMap(fileName) == dict);
		}
	}
}


SCENARIO("save dictionary")
{
	std::ostringstream output;
	WHEN("dictionary is empty")
	{
		std::map<std::string, std::string> dictionary = {};
		THEN("output is empty too")
		{
			SaveDictionaryInFile(dictionary, output);
			CHECK(output.str() == "");
		}
	}

	WHEN("dictionary is not empty")
	{
		std::map<std::string, std::string> dictionary = { {"cat", "кошка"},
										   {"my dog", "моя собака"} };
		THEN("output is empty too")
		{
			SaveDictionaryInFile(dictionary, output);
			CHECK(output.str() == "cat  кошка\nmy dog  моя собака\n");
		}
	}
}


SCENARIO("check if changes are saved")
{
	std::map<std::string, std::string> dictionary = { {"cat", "кошка"},
										   {"my dog", "моя собака"} };
	WHEN("the input character is not Y or y")
	{
		std::istringstream input("k");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());
		std::string fileName = "ExistingFile.txt";
		THEN("the program exit without saving changes")
		{
			CHECK(FinishWorkDictionary(fileName, dictionary) == "Изменения не сохранены. До свидания.\n");
		}
	}

	WHEN("wrong file created")
	{
		std::istringstream input("y");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());
		std::string fileName = "";
		THEN("the program ends without saving changes")
		{
			CHECK(FinishWorkDictionary(fileName, dictionary) == "Изменения не сохранены. Невозможно открыть файл \n");
		}
	}

	WHEN("file exists")
	{
		std::istringstream input("y");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());
		std::string fileName = "File.txt";
		THEN("the program ends whith saving changes")
		{
			CHECK(FinishWorkDictionary(fileName, dictionary) == "Изменения сохранены. До свидания.\n");
		}
	}
}

SCENARIO("add empty string")
{
	std::istringstream input("");
	std::streambuf* cinbuf = std::cin.rdbuf();
	std::cin.rdbuf(input.rdbuf());
	std::map<std::string, std::string> dictionary = {};
	std::string word = "dog";
	REQUIRE(AddWord(dictionary, word) == "Слово “dog” проигнорировано.\n");
}

SCENARIO("add not empty string")
{
	std::istringstream input("красный");
	std::streambuf* cinbuf = std::cin.rdbuf();
	std::cin.rdbuf(input.rdbuf());
	std::map<std::string, std::string> dictionary = {};
	std::string word = "red";
	REQUIRE(AddWord(dictionary, word) == "Слово “red” сохранено в словаре как “красный”.\n");
}

SCENARIO("input word")
{
	std::ostringstream out;
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	WHEN("the word is not found in map")
	{
		std::map<std::string, std::string> dictionary = {};
		std::string word = "dog";
		THEN("the program asks for a translation and process the result")
		{
			std::istringstream input("");
			std::streambuf* cinbuf = std::cin.rdbuf();
			std::cin.rdbuf(input.rdbuf());
			WriteTranslation(dictionary, word);
			std::cin.rdbuf(cinbuf);
			std::cout.rdbuf(coutbuf);
			CHECK(out.str() == "Неизвестное слово “dog”. Введите перевод или пустую строку для отказа.\nСлово “dog” проигнорировано.\n");

		}
	}

	WHEN("the word is found in map")
	{
		std::map<std::string, std::string> dictionary = { {"cat", "кошка, кот"} };
		std::string word = "cat";
		THEN("the program displays the translation of the found word")
		{
			WriteTranslation(dictionary, word);
			std::cout.rdbuf(coutbuf);
			CHECK(out.str() == "кошка, кот\n");

		}
	}

	WHEN("the word has letters in a different case")
	{
		std::map<std::string, std::string> dictionary = { {"the red square", "крассная площадь"} };
		std::string word = "The Red SqUare";
		THEN("the program displays the translation of the found losercase word")
		{
			WriteTranslation(dictionary, word);
			std::cout.rdbuf(coutbuf);
			CHECK(out.str() == "крассная площадь\n");

		}
	}
}


SCENARIO("check changes")
{
	std::ostringstream out;
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	WHEN("size of map hasn't changed")
	{
		std::map<std::string, std::string> dictionary = { {"i", "я"} };
		std::size_t sizeMap = 1;
		THEN("the program ends without changes")
		{
			CheckChangesAndFinishWork(sizeMap, dictionary, "empty.txt");
			std::cout.rdbuf(coutbuf);
			CHECK(out.str() == "Нет изменений для добавления в словарь. До новых встреч!\n");

		}
	}

	WHEN("size of map has changed")
	{
		std::map<std::string, std::string> dictionary = { {"i", "я"} };
		std::size_t sizeMap = 0;
		THEN("the program offers to save the changes")
		{
			std::istringstream input("");
			std::streambuf* cinbuf = std::cin.rdbuf();
			std::cin.rdbuf(input.rdbuf());
			CheckChangesAndFinishWork(sizeMap, dictionary, "empty.txt");
			std::cin.rdbuf(cinbuf);
			std::cout.rdbuf(coutbuf);
			CHECK(out.str() == "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\nИзменения не сохранены. До свидания.\n");

		}
	}
}