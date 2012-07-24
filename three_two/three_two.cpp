// three_two.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void doit(char* foo, int n) {
	int i = 0;
	short* moo = reinterpret_cast<short*>(foo);

	for (; n > 1; n--) {
		char c1 = foo[3*n - 3];
		char c2 = foo[3*n - 2];
		short j = ((short*)foo)[n-1];
		*((short*)(foo + 3*n - 3)) = j;
		if (n > 2) {
			for (i = 2*n - 2; i < 3*n - 5; i++) {
				foo[i] = foo[i+2];
			}
			foo[i++] = c1;
			foo[i] = c2;
		} else {
			foo[2] = c2;
		}
	}
}

int main(int argc, char* argv[])
{
	char foo[30];
	int i;
	for(i = 0; i < 10; i++) {
		short s = 252 + i;
		((short*)foo)[i] = s;
		foo[i+20] = 'a' + i;
	}

	doit(foo,10);

	for(i = 0; i < 10; i++) {
		std::cout << *((short*)(foo + 3*i)) << std::endl;
		std::cout << foo[3*i + 2] << std::endl;
	}

	return 0;
}

