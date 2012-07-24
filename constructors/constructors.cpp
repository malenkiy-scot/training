// constructors.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class parent {
public:
	parent() {
		std::cout << "Parent constructor called\n";
	}

	virtual ~parent() {
		std::cout << "Parent destructor called\n";
	}

	void* operator new(size_t size) {
		std::cout << "parent::new called with " << size << '\n';
		return ::operator new(size);
	}

	void operator delete(void* p) {
		std::cout << "parent::delete called\n";
		::operator delete(p);
	}
};

class child : public parent {
public:
	child() {
		std::cout << "Child constructor called\n";
	}

	~child() {
		std::cout << "Child destructor called\n";
	}

	void* operator new(size_t size) {
		std::cout << "child::new called with " << size << '\n';
		return ::operator new(size);
	}

	void operator delete(void* p) {
		std::cout << "child::delete called\n";
		::operator delete(p);
	}
};

void foo() {
	child* tmp = new child();
	parent* tmp1 = tmp;
	delete tmp1;
}

int main(int argc, char* argv[])
{
	foo();
	return 0;
}

