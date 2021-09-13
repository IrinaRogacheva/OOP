#pragma once

#include <iosfwd>
#include <optional>
#include <string>
#include <map>

void SaveDictionaryToFile(const std::map<std::string, std::string>& dictionary, std::ostream& output);

std::map<std::string, std::string> LoadDictionary(const std::string& inFileName);

std::string FinishWorkDictionary(const std::string& outFileName, const std::map<std::string, std::string>& dictionary);

std::string AddWord(std::map<std::string, std::string>& dictionary, const std::string& englWord);

void CheckChangesAndFinishWork(size_t sizeMap, const std::map<std::string, std::string>& dictionary, const std::string& fileName);

void WriteTranslation(std::map<std::string, std::string>& dictionary, const std::string& englWord);