
#include "stdafx.h"

#include <codecvt>
#include <cstdlib>
#include <cctype>
#include <algorithm>

#include "CompareWord.h"


//метод возвращает "успех" в случае, если слова различи¤ютс¤ лишь одной буквой
bool CompareWord::compareOneChar(const wstring& comparedWord, wstring& itemWord)
{
	bool firstChanceIgnored = false;
	bool successFind = false;

	auto iterInit = comparedWord.begin();
	auto iterSlovo = itemWord.begin();

	for (; iterSlovo < itemWord.end(); ++iterSlovo, ++iterInit) {
		*iterSlovo = towupper(*iterSlovo);

		if (*iterSlovo == *iterInit) continue;
		else if (firstChanceIgnored) break;
		else firstChanceIgnored = true;
	}

	if (iterSlovo == itemWord.end()) successFind = true;

	return successFind;
}

//метод осуществл¤ет поиск цепочки слов из словар¤ на основе рекурсии
void CompareWord::findChainWord(const wstring& comparedWord, int listNumber)
{
	for (auto slovo : dictionary) {

		if (slovo.length() != initWord.length() || slovo == endWord || slovo == initWord || slovo == comparedWord) continue;

		if (compareOneChar(comparedWord, slovo) &&
			std::find(chainWord[listNumber].begin(), chainWord[listNumber].end(), slovo) == chainWord[listNumber].end())
		{
			chainWord[listNumber].push_back(slovo);

			if (compareOneChar(endWord, slovo))
				break;
			else
				findChainWord(slovo, listNumber);

			if (comparedWord == initWord) listNumber++;
		}
	}
}

//чтение файла с начальными данными
void CompareWord::readInputFile(const wstring& dirInput)
{
	try {
		wifstream inputfile(dirInput);
		inputfile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

		wstring line;
		while (!inputfile.eof())
		{
			inputfile >> line;

			if (initWord.empty()) {
				initWord = line;
			}
			else {
				endWord = line;
				break;
			}
		}
		inputfile.close();
	}
	catch (std::exception& e)
	{
		wcout << e.what() << endl;
	}


	for (wstring::iterator it = initWord.begin(); it != initWord.end(); ++it)
		*it = towupper(*it);

	for (wstring::iterator it = endWord.begin(); it != endWord.end(); ++it)
		*it = towupper(*it);
}

//чтение файла с данными cловар¤
void CompareWord::readDictionaryFile(const wstring& dirDictionary)
{
	try {
		//чтение файла словар¤
		wifstream dictionaryfile(dirDictionary);
		dictionaryfile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));

		wstring line;
		while (!dictionaryfile.eof())
		{
			dictionaryfile >> line;
			dictionary.push_back(line);
		}
		dictionaryfile.close();

		chainWord.reserve(dictionary.size());

		for (auto i = 0; i < dictionary.size(); ++i) {
			chainWord.push_back(list<wstring>());
		}
	}
	catch (std::exception& e)
	{
		wcout << e.what() << endl;
	}
}
