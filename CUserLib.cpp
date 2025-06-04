#include "CUserLib.h"

#include "CAllocator.h"

CUserLib gUserLib;

CUserLib::CUserLib() {
	this->mUserLib = LoadLibraryA("user32.dll");
}

CUserLib::~CUserLib() {
	FreeLibrary(this->mUserLib);
}

void CUserLib::Open() {
	new(&gUserLib)CUserLib;
}

void CUserLib::Close() {
	gUserLib.~CUserLib();
}
