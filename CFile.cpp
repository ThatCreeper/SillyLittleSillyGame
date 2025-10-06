#include "CFile.h"

#include "CoreWin.h"
#include "CAllocator.h"

CFile::CFile(const CString &Path, EFileType Type)
{
	Open(Path.Data(), Type);
}

CFile::CFile(CStringView Path, EFileType Type)
{
	CString String(Path);
	Open(String.Data(), Type);
}

CFile::~CFile()
{
	if (this->mData)
		delete[] this->mData;
	CloseHandle(this->mFile);
}

CStringView CFile::ReadAll()
{
	if (this->mData)
		return CStringView(this->mData, this->mSize);
	this->mData = new char[this->mSize + 1];
	int OutRead = 0;
	ReadFile(this->mFile, this->mData, this->mSize, &OutRead, nullptr);
	this->mData[OutRead] = '\0';
	return CStringView(this->mData, this->mSize);
}

void CFile::Open(const char *Path, EFileType Type)
{
	int Permission = 0;
	int Command = 0;

	switch (Type) {
	case EFileType::Read:
		Permission = 0x80000000;
		Command = 3 /* Open Existing */;
		break;
	case EFileType::Write:
		Permission = 0x40000000;
		Command = 2 /* Create Always */;
		break;
	case EFileType::Append:
		// Implementation is a later problem.
		// Essentially, just open WRITE and
		// fseek(size).
		Panic();
		break;
	default:
		Panic();
		break;
	}
	this->mFile = CreateFileA(Path, Permission, 0, nullptr, Command, 0x80 /* Normal */, nullptr);
	Assert(this->mFile);
	Assert(this->mFile != (void *)-1);
	this->mData = nullptr;
	this->mSize = 0;
	if (Type != EFileType::Write) {
		unsigned long long FileSize = 0;
		GetFileSizeEx(this->mFile, &FileSize);
		this->mSize = (int) FileSize;
	}
}
