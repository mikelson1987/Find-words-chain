// Win32Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "CompareWord.h"

int _tmain(int argc, _TCHAR* argv[])
{
	wstring dirInput, dirDictionary;

	// разбор входных параметров
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

	wcout << L"Путь к входному файлу: " << dirInput << endl;
	wcout << L"Путь к файлу словаря: " << dirDictionary << endl;
	wcout << L"Поиск цепочки слов:" << endl;

	//передача объекта данных в объект поиска цепочек слов
	CompareWord word;
	//чтение файла начальных данных
	word.readInputFile(dirInput);
	//чтение файла данных словаря
	word.readDictionaryFile(dirDictionary);

	//инициализация начальных размеров
	auto& chainWord = word.getChainWord();

	//поиск цепочек слов
	const wstring& compareWord = word.getInitWord();
	word.findChainWord(compareWord, 0);

	int numberChain = 0;

	//отображение найденных цепочек
	for (auto index = 0; index < chainWord.size(); ++index) {
		if (chainWord[index].empty()) continue;

		wcout << L"Цепочка: " << ++numberChain << endl;
		wcout << word.getInitWord() << endl;
		for (auto& slovo : chainWord[index]) {
			wcout << slovo << endl;
		}
		wcout << word.getEndWord() << endl;
	}
	
	system("pause");

	return 0;
}

