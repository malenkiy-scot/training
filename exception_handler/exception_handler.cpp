#include "stdafx.h"


using std::cout;
using std::endl;


struct EXCEPTION_REGISTRATION
{
   EXCEPTION_REGISTRATION *prev;
   DWORD handler;
};


EXCEPTION_DISPOSITION myHandler(
    _EXCEPTION_RECORD *ExcRecord,
    void * EstablisherFrame, 
    _CONTEXT *ContextRecord,
    void * DispatcherContext)
{
	cout << "In the exception handler" << endl;
	cout << "Just a demo. exiting..." << endl;
	exit(0);
	return ExceptionContinueExecution; //will not reach here

}

int g_div = 0;

class foo {
};

void bar()
{
	//initialize EXCEPTION_REGISTRATION structure

	EXCEPTION_REGISTRATION reg, *preg = &reg;
	reg.handler = (DWORD)myHandler;
	
	//get the current head of the exception handling chain	

	DWORD prev;
	_asm
	{
		mov EAX, FS:[0]
		mov prev, EAX
	}
	reg.prev = (EXCEPTION_REGISTRATION*) prev;
	
	//register it!

	_asm
	{
		mov EAX, preg
		mov FS:[0], EAX
	}

	//generate the exception

	int j = 10 / g_div;  //Exception. Divide by 0. 
	throw new foo();
}

int main()
{
	bar();
	return 0;
}
