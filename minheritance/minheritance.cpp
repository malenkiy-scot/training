// minheritance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class A {
public:
    A() { std::cout << "A"; }
};

class B : public A {
public:
    B() { std::cout << "B"; }
};

class C {
public:
    C() { printSelf(); };
    virtual void printSelf() { std::cout << "C"; }
};

class D : public C {
public:
    D() { printSelf(); };
    virtual void printSelf() { std::cout << "D"; }
};

class E : public D, public A, public B
{
public:
    E() { std::cout << "E"; }
private:
    //B b;
    //C c;
};

int main(int argc, char* argv[])
{
    E* e = 0;
	delete e;
    //std::cout << std::endl << "sizeof(A) = " << sizeof(A) 
    //          << std::endl << "sizeof(B) = " << sizeof(B)
    //          << std::endl << "sizeof(C) = " << sizeof(C)
    //          << std::endl << "sizeof(D) = " << sizeof(D)
    //          << std::endl << "sizeof(E) = " << sizeof(E)
    //          << std::endl;

	//std::cout << std::endl << "E* = " << &e
	//	       << std::endl << "(D*)(E*) = " << dynamic_cast<D*>(&e)
	//		   << std::endl << "(A*)(E*) = " << dynamic_cast<A*>(&e)
	//		   << std::endl << "(B*)(E*) = " << dynamic_cast<B*>(&e)
	//		   << std::endl;

	return 0;
}
