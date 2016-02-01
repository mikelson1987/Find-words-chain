
#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <locale>


using namespace std;

class CompareWord {
	//types
public:
	typedef vector<list<wstring>> ChainWordListType;

	//values
private:
	//начальное и конечное слово
	wstring initWord, endWord;
	//словарь вход¤щих слов
	list<wstring> dictionary;
	//цепочки слов
	ChainWordListType chainWord;

	//methods
public:
	CompareWord() {};
	bool compareOneChar(const wstring& comparedWord, wstring& itemWord);
	void findChainWord(const wstring& comparedWord, int listNumber);
	void readInputFile(const wstring& dirInput);
	void readDictionaryFile(const wstring& dirDictionary);

	const wstring& InitWord() const {
		return initWord;
	}

	const wstring& EndWord() const {
		return endWord;
	}

	ChainWordListType& getChainWord() {
		return chainWord;
	}

	list<wstring>& getDictionary() {
		return dictionary;
	}

	const wstring& getInitWord() const {
		return initWord;
	}

	const wstring& getEndWord() const{
		return endWord;
	}
};
