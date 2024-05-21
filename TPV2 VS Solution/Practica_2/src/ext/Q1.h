#pragma once
#include <iostream>


class IntPtr {
public:
	int* p;

	IntPtr() :
		IntPtr(0) {
	}

	IntPtr(int n) {
		p = new int(n);
	}


	IntPtr(const IntPtr& o) :
		IntPtr(*o.p) {}

	IntPtr(IntPtr&& o) noexcept {
		p = o.p;
		o.p = nullptr;
	}


	IntPtr& operator=(const IntPtr& o) {

		p = new int(*o.p);

		return *this;
	}


	IntPtr& operator=(IntPtr&& o) noexcept {

		p = o.p;
		o.p = nullptr;

		return *this;
	}



	~IntPtr() {
		if (p != nullptr) {
			delete p;
		}
	}

};

void main_q1() {
	IntPtr a(1);
	IntPtr b(a);
	IntPtr c(std::move(a));

	IntPtr d;
	d = c;

	IntPtr e;
	e = std::move(b);
}

