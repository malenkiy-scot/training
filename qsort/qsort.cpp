// qsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <iostream>

template <typename T>
class vector {
	T* elements;
	int num;

	static void swap(T* a, T* b) {
		T tmp = *a;
		*a = *b;
		*b = tmp;
	}
	void qsortRange(T* pb, T* pe) {
		//T* foo;
		//std::cout << "Sorting: ";
		//for (foo = pb; foo <= pe; foo++) {
		//	std::cout << *foo << ' ';
		//}
		//std::cout << '\n';
		//if (pe <= pb) {
		//	return;
		//}
		//if (pe == pb + 1) {
		//	if (*pe < *pb) {
		//		swap(pb, pe);
		//	}
		//	return;
		//}
		if (pb >= pe) {
			return;
		}
		swap(pb, (pe - pb)/2 + pb);
		T med = *pb;

		T* tmpb = pb-1;
		T* tmpe = pe+1;

		while (true) {
			while (*(++tmpb) < med);
			while (*(--tmpe) > med);
			if (tmpe > tmpb) {
				swap(tmpb, tmpe);
			} else {
				break;
			}
		}
		dump();
		qsortRange(pb, tmpe);
		qsortRange(tmpe+1, pe);
	}

public:
	vector(T arr_[], int num_) {
		num = num_;
		elements = new T[num];
		for (int i = 0; i < num; i++) {
			elements[i] = arr_[i];
		}
	}

	void dump() {
		for (int i = 0; i < num; i++) {
			std::cout << elements[i] << ' ';
		}
		std::cout << '\n';
	}
	bool operator==(vector<T>& other) {
		if (other.num != num) {
			return false;
		}
		for (int i = 0; i < num; i++) {
			if (other.elements[i] != elements[i]) {
				return false;
			}
		}
		return true;
	}

	void qsort() {
		qsortRange(elements, elements+num-1);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	int arr[] = {2,3,6,1,8,9,7,12,5,10,4,11};
	vector<int> myArray(arr, 12);
	assert(myArray == vector<int>(arr, 12));
	myArray.dump();
	myArray.qsort();
	myArray.dump();
	int arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12};
	assert(myArray == vector<int>(arr1,12));
	return 0;
}
