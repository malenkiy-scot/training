// heapsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


class heap {
private:
	int size_;
	int* heap_;

public:
	heap(int inValues[], int size) {
		heap_ = new int[size];
		size_ = size;

		for (int i = 0; i < size_; i++) {
			heap_[i] = inValues[i];
		}
		makeHeap();
	}

	int* sort() {
		while(size_ > 0) {
			swap(0, size_ - 1);
			size_--;
			heapify(0);
		}
		return heap_;
	}

private:
	int parent(int i) {
		return (i + 1)/2 - 1;
	}
	int left(int i) {
		int ret = 2*i + 1; 
		return ret < size_ ? ret : -1;
	}
	int right(int i) {
		int ret = 2*i + 2; 
		return ret < size_ ? ret : -1;
	}
	void swap(int i, int j) {
		if (i < size_ && i >= 0 && j < size_ && j >= 0) {
			int t = heap_[i];
			heap_[i] = heap_[j];
			heap_[j] = t;
		}
	}

	void heapify(int index) {
		while(true) {
			int l = left(index);
			int r = right(index);
			int t = 0;

			if (l < 0 && r < 0)
				return;

			if(l >=0 && r>= 0 && heap_[r] >= heap_[l]) {
				t = r;
			} else if (l >= 0){
				t = l;
			} else {
				t = r;
			}
			if(heap_[index] < heap_[t]) {
				swap(index, t);
				index = t;
			} else {
				return;
			}
		}
	}
	void makeHeap() {
		for(int i = size_/2; i >= 0; i--) {
			heapify(i);
		}
	}
};

int main(int argc, char* argv[])
{
	int foo[] = {34,56,12,4,-3,4,-12,-3,18,0,12,123,32,456,98,-101,11,35,76};
	heap myHeap(foo, 19);
	int* boo = myHeap.sort();

	for (int i = 0; i < 19; i++) {
		std::cout << *(boo+i) << '\n';
	}
	return 0;
}

