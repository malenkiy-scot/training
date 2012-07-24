// KMP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void createMap(int map[], char* pat, int patLen) {
	map[0] = 0;

	int matchLen = 0;
	int patPos = 0;

	for(patPos = 1; patPos < patLen; patPos++) {
		while (matchLen > 0 && pat[matchLen] != pat[patPos]) {
			matchLen = map[matchLen-1];
		}
		if (pat[matchLen] == pat[patPos]) {
			matchLen++;
		}
		map[patPos] = matchLen;
	}
}

void KMP(char* pat, char* str) {
	int patLen = strlen(pat);
	int strLen = strlen(str);

	int* map = new int[patLen];
	createMap(map, pat, patLen);

	int matchLen = 0;
	int strPos = 0;

	for(strPos = 0; strPos < strLen; strPos++) {
		while(matchLen > 0 && pat[matchLen] != str[strPos]) {
			matchLen = map[matchLen-1];
		}
		if (pat[matchLen] == str[strPos]) {
			matchLen++;
		}
		if (matchLen == patLen) {
			std::cout << "Match found at shift: " << strPos - patLen << std::endl;
			matchLen = map[matchLen-1];
		}
	}
	delete[] map;
}

int main(int argc, char* argv[])
{
	if (argc < 3) {
		std::cout << "Format: " << argv[0] << " <pattern> <string>" << std::endl;
	}
	char* pat = argv[1];
	char* str = argv[2];

	KMP(pat, str);
	return 0;
}

