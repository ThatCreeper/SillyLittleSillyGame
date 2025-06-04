#include "CString.h"

#include "CAllocator.h"

CString::CString(const char *String, int Length)
{
	// Zero-termed for compat
	this->mString = new char[Length + 1];
	this->mLength = Length;

	for (int i = 0; i < Length; i++) {
		this->mString[i] = String[i];
	}
	this->mString[Length] = '\0';
}

CString::CString(CStringView String)
	: CString(String.Data(), String.Length())
{
}

CString::CString(CString &&Moved) noexcept
{
	this->mString = Moved.mString;
	this->mLength = Moved.mLength;
	Moved.mString = 0;
	Moved.mLength = 0;
}

CString::CString()
{
	this->mString = new char[1];
	this->mLength = 0;

	this->mString[0] = '\0';
}

CString::~CString()
{
	delete[] this->mString;
}

char *CString::Data()
{
	return this->mString;
}

int CString::Length()
{
	return this->mLength;
}

CStringView CString::View()
{
	return CStringView(this->mString, this->mLength);
}

void CString::operator+=(CStringView Other)
{
	this->mString = (char *)gAllocator.Resize(this->mString, this->mLength + Other.Length() + 1);
	
	for (int i = 0; i < Other.Length(); i++) {
		this->mString[this->mLength + i] = Other.Data()[i];
	}
	this->mString[this->mLength + Other.Length()] = '\0';

	this->mLength += Other.Length();
}

void CString::Expand(int Characters)
{
	this->mString = (char *)gAllocator.ResizeZeroed(this->mString, this->mLength + Characters + 1);
	this->mLength += Characters;
}

void CString::AddInteger(int Integer)
{
	bool Negative = Integer < 0;
	int Abs = Negative ? -Integer : Integer;
	
	int Digits = 1;
	int Counter = Abs;
	while (Counter >= 10) {
		Digits++;
		Counter /= 10;
	}

	int AlteredIndex = this->mLength;
	this->Expand(Digits + (Negative ? 1 : 0));

	if (Negative)
		this->mString[AlteredIndex++] = '-';

	while (Digits--) {
		int Digit = (Abs / Pow(10, Digits)) % 10;
		this->mString[AlteredIndex++] = '0' + Digit;
	}
}
