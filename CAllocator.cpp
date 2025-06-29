#include "CAllocator.h"

#include "CoreWin.h"

CAllocator gAllocator;

inline CAllocator::CAllocator() {
	//this->mHeap = HeapCreate(0 /* No Flags (Execute, etc) */, 1 /* One Page Minimum Size */, 0 /* No Maximum Size */);
	this->mHeap = GetProcessHeap();
	if (!this->mHeap)
		Panic();
}

inline CAllocator::~CAllocator() {
	// HeapDestroy(this->mHeap);
}

inline void *CAllocator::Allocate(size_t Size) {
	if (!Size)
		return nullptr;
	return HeapAlloc(this->mHeap, 0 /* No Flags */, Size);
}

inline void *CAllocator::AllocateZeroed(size_t Size) {
	if (!Size)
		return nullptr;
	return HeapAlloc(this->mHeap, 0x8 /* Zeroed */, Size);
}

inline void CAllocator::Free(void *Pointer) {
	if (!Pointer)
		return;
	HeapFree(this->mHeap, 0, Pointer);
}

void *CAllocator::Resize(void *Pointer, size_t NewSize)
{
	if (!Pointer)
		return this->Allocate(NewSize);
	return HeapReAlloc(this->mHeap, 0 /* No Flags */, Pointer, NewSize);
}

void *CAllocator::ResizeZeroed(void *Pointer, size_t NewSize)
{
	if (!Pointer)
		return this->AllocateZeroed(NewSize);
	return HeapReAlloc(this->mHeap, 0x8 /* Zeroed */, Pointer, NewSize);
}

void *operator new(size_t Size, void *Into) {
	return Into;
}

void *operator new(size_t Size) {
	return gAllocator.Allocate(Size);
}

void *operator new[](size_t Size) {
	return gAllocator.Allocate(Size);
}

void operator delete(void *Pointer) {
	gAllocator.Free(Pointer);
}

void operator delete(void *Pointer, unsigned long long Size) {
	gAllocator.Free(Pointer);
}

void operator delete[](void *Pointer) {
	gAllocator.Free(Pointer);
}
