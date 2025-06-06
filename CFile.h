#pragma once

#include "Core.h"
#include "CStringView.h"
#include "CString.h"

enum class EFileType {
	Read,
	Write,
	Append
};

class CFile
{
public:
	CFile(const CString &Path, EFileType Type);
	CFile(CStringView Path, EFileType Type);
	~CFile();

	CStringView ReadAll();

protected:
	void Open(const char *Path, EFileType Type);

	HFile mFile;
	char *mData;
	int mSize;
};

