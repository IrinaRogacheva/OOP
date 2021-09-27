#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Dictionary/Dictionary.h"

using namespace std;

SCENARIO("Read dictionary file")
{
	WHEN("Input file does not exist")
	{
		ifstream file("NoExist.txt");
		THEN("Dictionary map is empty")
		{
			map<string, string> emptyDict = {};
			CHECK(ReadDictFile(file) == emptyDict);
		}
	}

	WHEN("Input file is empty")
	{
		ifstream file("empty.txt");
		THEN("Dictionary map is empty")
		{
			map<string, string> emptyDict = {};
			CHECK(ReadDictFile(file) == emptyDict);
		}
	}

	WHEN("Input file is not empty")
	{
		ifstream file("non_empty.txt");
		THEN("Key is string before \"|\" character, value is string after this character")
		{
			map<string, string> dict = { { "The Red Square", "Красная Площадь" }, { "ball", "мяч" }, { "cat", "кот,кошка" } };
			CHECK(ReadDictFile(file) == dict);
		}
	}
}

SCENARIO("Check Saving Of Word")
{
	WHEN("An empty string was passed as a translation")
	{
		std::istringstream input("");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());

		std::ostringstream output;
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(output.rdbuf());

		THEN("The translation was not saved")
		{
			map<string, string> dict = { { "ball", "мяч" }, { "cat", "кот,кошка" } };
			BilingualDictionary bilingualDict = { dict, GenerateReverseDictionary(dict) };
			CheckSavingOfWord(bilingualDict, "xfghiudfgiu");
			map<string, string> expectedDict = { { "ball", "мяч" }, { "cat", "кот,кошка" } };
			CHECK(dict  == expectedDict);
			CHECK(output.str() == "Неизвестное слово \"xfghiudfgiu\". Введите перевод или пустую строку для отказа.\n>Слово \"xfghiudfgiu\" проигнорировано.\n");
		}
		std::cin.rdbuf(cinbuf);
		std::cout.rdbuf(coutbuf);
	}

	WHEN("As a translation was passed not empty string")
	{
		std::istringstream input("медведь");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());

		std::ostringstream output;
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(output.rdbuf());

		THEN("The translation was saved")
		{
			map<string, string> dict = { { "ball", "мяч" }, { "cat", "кот,кошка" } };
			BilingualDictionary bilingualDict = { dict, GenerateReverseDictionary(dict) };
			CheckSavingOfWord(bilingualDict, "bear");
			map<string, string> expectedDict = { { "ball", "мяч" }, { "cat", "кот,кошка" }, { "bear", "медведь" } };
			CHECK(bilingualDict.dictionary == expectedDict);
			CHECK(output.str() == "Неизвестное слово \"bear\". Введите перевод или пустую строку для отказа.\n>Слово \"bear\" сохранено в словаре как \"медведь\".\n");

			AND_THEN("In reverse dictionary was added new reverse translate")
			{
				map<string, string> expectedReverseDict = GenerateReverseDictionary(expectedDict);
				map<string, string> reverseDict = GenerateReverseDictionary(dict);
				CHECK(bilingualDict.reverseDictionary == expectedReverseDict);
			}
		}

		std::cin.rdbuf(cinbuf);
		std::cout.rdbuf(coutbuf);
	}
}

SCENARIO("Process User Input")
{
	WHEN("The entered string is equal to ...")
	{
		std::istringstream input("...");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());

		std::ostringstream output;
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(output.rdbuf());

		THEN("The function execution is interrupted")
		{
			map<string, string> dict = { { "ball", "мяч" }, { "cat", "кот,кошка" } };
			BilingualDictionary bilingualDict = { dict, GenerateReverseDictionary(dict) };
			ProcessUserInput(bilingualDict);
			map<string, string> expectedDict = { { "ball", "мяч" }, { "cat", "кот,кошка" } };
			CHECK(dict == expectedDict);
			CHECK(output.str() == "Введите слово, которое хотите перевести. Для выхода введите многоточие \"...\"\n>");
		}
		std::cin.rdbuf(cinbuf);
		std::cout.rdbuf(coutbuf);
	}

	WHEN("Entering a word that is in the dictionary")
	{
		std::istringstream input("cat\n...");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());

		std::ostringstream output;
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(output.rdbuf());

		THEN("The translation of the word is displayed")
		{
			map<string, string> dict = { { "ball", "мяч" }, { "cat", "кот,кошка" }, { "котище", "cat" } };
			BilingualDictionary bilingualDict = { dict, GenerateReverseDictionary(dict) };

			ProcessUserInput(bilingualDict);
			CHECK(output.str() == "Введите слово, которое хотите перевести. Для выхода введите многоточие \"...\"\n>кот,кошка,котище\n>");
		}
		std::cin.rdbuf(cinbuf);
		std::cout.rdbuf(coutbuf);
	}

	WHEN("Entering a word that is in the dictionary in any case")
	{
		std::istringstream input("BaLl\n...");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());

		std::ostringstream output;
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(output.rdbuf());

		THEN("Regardless of the case, the word was found")
		{
			map<string, string> dict = { { "ball", "мяч" }, { "cat", "кот,кошка" } };
			BilingualDictionary bilingualDict = { dict, GenerateReverseDictionary(dict) };

			ProcessUserInput(bilingualDict);
			CHECK(output.str() == "Введите слово, которое хотите перевести. Для выхода введите многоточие \"...\"\n>мяч\n>");
		}
		std::cin.rdbuf(cinbuf);
		std::cout.rdbuf(coutbuf);
	}
}

SCENARIO("Check Saving Of Changes In Dictionary")
{
	WHEN("The entered string is equal to Y or y")
	{
		std::istringstream input("Y");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());

		std::ostringstream output;
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(output.rdbuf());

		THEN("Changes are saved")
		{
			map<string, string> dict = { { "ball", "мяч" }, { "cat", "кот,кошка" } };
			CheckSavingOfChangesInDictionary(dict, "output.txt");
			CHECK(output.str() == "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n>Изменения сохранены. До свидания.\n");
			
			ifstream output("output.txt");
			string str;
			getline(output, str);
			CHECK(str == "ball|мяч");
			getline(output, str);
			CHECK(str == "cat|кот,кошка");
		}
		std::cin.rdbuf(cinbuf);
		std::cout.rdbuf(coutbuf);
	}

	WHEN("The entered string is not equal to Y or y")
	{
		std::istringstream input("no");
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(input.rdbuf());

		std::ostringstream output;
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(output.rdbuf());

		THEN("Changes are not saved")
		{
			map<string, string> dict = { { "ball", "мяч" }, { "cat", "кот,кошка" } };
			CheckSavingOfChangesInDictionary(dict, "empty.txt");
			CHECK(output.str() == "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n>Изменения не были сохранены. До свидания.\n");

			ifstream output("empty.txt");
			string str;
			getline(output, str);
			CHECK(str == "");
		}
		std::cin.rdbuf(cinbuf);
		std::cout.rdbuf(coutbuf);
	}
}

SCENARIO("Generate Reverse Dictionary")
{
	WHEN("Map of reverse translates is generated")
	{
		map<string, string> dict = {{ "ball", "мяч" }, { "cat", "кот,кошка" }, { "dependable", "надежный" }, { "reliable", "надежный" }};
		map<string, string> reverseDict = GenerateReverseDictionary(dict);

		THEN("The map of reverse translations must match the original dictionary")
		{
			map<string, string> expectedReverseDict = { { "мяч", "ball" }, { "кот", "cat" }, { "кошка", "cat" }, { "надежный", "dependable,reliable" } };
			CHECK(reverseDict == expectedReverseDict);
		}
	}
}

SCENARIO("Write reverse translate")
{
	WHEN("The entered word is in the reverse dictionary")
	{
		std::ostringstream output;
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(output.rdbuf());

		THEN("Values from both dictionaries are displayed")
		{
			map<string, string> dict = { { "ball", "мяч" }, { "cat", "кот,кошка" } };
			BilingualDictionary bilingualDict = { dict, GenerateReverseDictionary(dict) };
			string str = "кошка";
			WriteTranslate(str, bilingualDict);
			CHECK(output.str() == "cat\n");
		}
		std::cout.rdbuf(coutbuf);
	}
}