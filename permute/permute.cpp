// permute.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void swap(char* p, char* q) {
	char c = *p;
	*p = *q;
	*q = c;
}

void reverse(char* s) {
	int n = strlen(s);
	for (int i = 0; i < n - 1 - i; i++) {
		swap(s+i, s+n-1-i);
	}
}

void permute(char* s) {
	int n = strlen(s);
	int i = 0, l = 0, k = 0;

	while(true) {
		std::cout << s << '\n';
		for (i = 0, k = -1; i < n - 1; i++) {
			if(*(s+i) < *(s+i+1))
				k = i;
		}
		if (k < 0)
			return;
		for (i = k+1; i < n; i++) {
			if(*(s+i) > *(s+k))
				l = i;
		}
		swap(s+k,s+l);
		reverse(s+k+1);
	}
}

int main(int argc, char* argv[])
{
	char* s = argv[1];
	permute(s);
	return 0;
}

