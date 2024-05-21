#pragma once

#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <vector>

template<typename T>
class ObjectPool {
public:

	using iterator = T*;

	T** pool;

	int nUsed = 0;
	int size;

	ObjectPool(std::size_t size) :size(size) {

		pool = new T * [size];

		for (int i = 0; i < size; i++) {

			pool[i] = nullptr;

		}
	}

	virtual ~ObjectPool() {

		for (int i = 0; i < nUsed; i++) {
			delete pool[i];
			pool[i] = nullptr;
			nUsed = 0;
		}
	}

	T* alloc() {
		assert(nUsed < size);
		return pool[nUsed++];
	}

	//borramos el elemento y recolocamos los usados, para tener a todos los usados consecutivos
	void free(T* p) {

		int i = 0;

		while (i < nUsed && p == pool[i]) i++;

		delete p;
		pool[i] = nullptr;

		nUsed--;

		while (i <= nUsed && i < size - 1) {
			pool[i] = pool[i + 1];
		}

		pool[i + 1] = nullptr;

	}

	iterator begin() {

		return pool[0];
	}

	iterator end() {
		return pool[nUsed];
	}

private:
};

struct Ent {
};

// ejemplo de uso
void main_q2() {
	ObjectPool<Ent> ent_pool(20);

	for (Ent& e : ent_pool) {
		// ...
	}

	std::vector<Ent*> v;

	for (int i = 0; i < 10; i++)
		v.push_back(ent_pool.alloc());

	for (Ent* e : v)
		ent_pool.free(e);
}

