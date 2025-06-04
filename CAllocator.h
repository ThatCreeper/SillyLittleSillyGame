#pragma once

#include "Core.h"

class CAllocator {
public:
	CAllocator();
	~CAllocator();

	void *Allocate(size_t Size);
	void *AllocateZeroed(size_t Size);

	void Free(void *Pointer);

protected:
	HHeap mHeap;
};

extern CAllocator gAllocator;

void *operator new(size_t Size, void *Into);

void *operator new(size_t Size);
void *operator new[](size_t Size);

void operator delete(void *Pointer);
void operator delete(void *Pointer, unsigned long long Size);
void operator delete[](void *Pointer);