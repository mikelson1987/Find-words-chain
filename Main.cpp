// Win32Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>
#include <list>
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <cctype>
#include <algorithm>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	wstring initWord, endWord;
	wstring dirInput, dirDictionary;
	
	list<wstring> dictionary;

	for (int i = 1; i < argc; ++i)	{
		if (wcscmp(argv[i], L"") != 0)	{
			if (dirInput.empty())
				dirInput = argv[i];
			else if (dirDictionary.empty()) {
				dirDictionary = argv[i];
				break;
			}
		}
	}

	setlocale(LC_ALL, "");

	wcout << L"Input directory: " << dirInput << endl;
	
	wifstream inputfile(dirInput);
	inputfile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	wstring line;
	while (!inputfile.eof())
	{
		inputfile >> line;
		wcout << line << endl;

		if (initWord.empty()) {
			initWord = line;
		}
		else {
			endWord = line;
			break;
		}
	}
	inputfile.close();

	for (wstring::iterator it = initWord.begin(); it != initWord.end(); ++it)
		*it = towupper(*it);

	for (wstring::iterator it = endWord.begin(); it != endWord.end(); ++it)
		*it = towupper(*it);



	wcout << L"Dictionary directory: " << dirDictionary << endl;

	wifstream dictionaryfile(dirDictionary);
	dictionaryfile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	while (!dictionaryfile.eof())
	{
		dictionaryfile >> line;
		wcout << line << endl;

		dictionary.push_back(line);
	}
	dictionaryfile.close();

	bool findInLastStep = false;
	std::wstring& compareWord = initWord;
	
	wcout << L"Поиск цепочки слов:" << endl;

	for(auto& slovo : dictionary) {

		bool firstChanceIgnored = false;

		if (slovo.length() != initWord.length()) continue;

		if (findInLastStep && compareWord != initWord && slovo == endWord) break;

		
		auto iterInit = compareWord.begin();
		auto iterSlovo = slovo.begin();

		for (; iterSlovo != slovo.end(); ++iterSlovo, ++iterInit) {
			*iterSlovo = towupper(*iterSlovo);
			
			if (*iterSlovo == *iterInit) continue;
			else if (firstChanceIgnored) break;
			else firstChanceIgnored = true;
		}

		if (iterSlovo == slovo.end()) {
			findInLastStep = true;
			compareWord = slovo;
			wcout << slovo << endl;
		}
		else {
			findInLastStep = false;
		}

	}
	
	system("pause");

	return 0;
}

//static int compare(const char* s1, const char* s2, size_t n) {
//	while (n-- != 0) {
//		if (toupper(*s1) < toupper(*s2)) return -1;
//		if (toupper(*s1) > toupper(*s2)) return 1;
//		++s1; ++s2;
//	}
//	return 0;
//}
