#pragma once

#include "CStringView.h"

class CString
{
public:
	CString(const char *String, int Length);
	CString(CStringView String);
	CString(CString &&Moved) noexcept;
	CString();
	~CString();

	void operator=(CStringView String);

	char *Data() const;
	int Length() const;
	CStringView View() const;

	void operator+=(CStringView Other);

	void Expand(int Characters);

	void AddInteger(int Integer);

protected:
	char *mString;
	int mLength;
};

