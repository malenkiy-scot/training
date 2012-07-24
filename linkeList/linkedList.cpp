// linkeList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


template <typename T>
class linkedList {
private:
	struct Node {
		T data;
		Node* next;
	};

	struct _iter {
		Node* p;
		_iter& next();
		_iter insert(T& el);
		T& operator*();
		T& operator*() const;
	};

public:
	typedef const _iter const_iter;
	typedef _iter iter;

private:
	iter last;
	iter first;

public:
	void push(T& el) {
		Node* n = new Node;
		n->next = 0;
		last = n;
		if (first == 0) {
			first = n;
		}
		n->data = el;
	}

	const_iter first_const_iter;
	const const_iter last_const_iter;
	iter first_iter;
	const iter last_iter;

	linkedList() : last_const_iter(0), last_iter(0) {
		first = last = 0;
		first_const_iter = 0;
		first_iter = 0;
	}

	~linkedList();
};

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

