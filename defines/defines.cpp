// defines.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define FOO(x,y) (x+y)
#pragma push_macro("FOO")
#undef FOO
#define FOO 5

int main(int argc, char* argv[])
{
	//std::cout << FOO(1,2) << std::endl; // error
	std::cout << FOO << std::endl; // ok

	#pragma pop_macro("FOO")

	std::cout << FOO(1,2) << std::endl; // ok
	//std::cout << FOO << std::endl; // error

	return 0;
}

