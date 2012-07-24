// FizzBuzz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	for (int i = 1, j = 1, k = 1; i < 20; j -= (++j/3)*3, k -= (++k/5)*5, i++){
		std::cout << i;
		if (!j) std::cout << "Fizz";
		if (!k) std::cout << "Buzz";
		std::cout << std::endl;
	}
	return 0;
}

