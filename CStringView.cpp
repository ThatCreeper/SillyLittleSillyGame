#include "CStringView.h"

static int ZeroTerminatedStringLength(const char *String) {
	int Length = 0;
	while (*(String++) != '\0')
		Length++;
	return Length;
}

CStringView::CStringView(const char *String, int Length)
{
	this->mData = String;
	this->mLength = Length;
}

CStringView::CStringView(const char *String) {
	this->mData = String;
	this->mLength = ZeroTerminatedStringLength(String);
}

const char *CStringView::Data() const {
	return this->mData;
}

int CStringView::Length() const {
	return this->mLength;
}

bool CStringView::Invalid() const
{
	return !this->mData || !this->mLength;
}

int CStringView::IndexOfFirstOccurance(char Character) const
{
	for (int i = 0; i < this->mLength; i++) {
		if (this->mData[i] == Character)
			return i;
	}

	return this->mLength;
}

int CStringView::ParseInteger() const
{
	int Result = 0;
	int Negative = false;
	int Index = 0;

	if (this->mLength < 1)
		return 0;
	if (this->mData[0] == '-') {
		Negative = true;
		Index++;
	}
	
	while (Index < this->mLength) {
		char Character = this->mData[Index++];

		if (Character == '.')
			continue;

		if (Character < '0' || Character > '9')
			return Negative ? -Result : Result;

		Result *= 10;
		Result += Character - '0';
	}
	return Negative ? -Result : Result;
}

float CStringView::ParseFloat() const
{
	return (float)this->ParseInteger() / 1000.f;
}

CStringView CStringView::SubString(int Start, int Length) const
{
	if (Start < 0)
		Start = 0;
	if (Length < 0)
		Length = 0;
	if (Start >= this->mLength)
		return CStringView(nullptr, 0);
	if (Start + Length > this->mLength)
		Length = this->mLength - Start;
	return CStringView(this->mData + Start, Length);
}

static bool IsWhiteSpace(char Character) {
	return Character == ' ' || Character == '\t' || Character == '\r' || Character == '\n';
}

CStringView CStringView::Trimmed() const
{
	int WhiteSpaceStart = 0;
	for (int i = 0; i < this->mLength; i++) {
		char Character = this->mData[i];
		if (IsWhiteSpace(Character))
			continue;
		WhiteSpaceStart = i;
		break;
	}

	int WhiteSpaceEnd = 0;
	for (int i = this->mLength; i > 0; i--) {
		char Character = this->mData[i - 1];
		if (IsWhiteSpace(Character))
			continue;
		WhiteSpaceEnd = i;
		break;
	}

	return this->SubString(WhiteSpaceStart, WhiteSpaceEnd - WhiteSpaceStart);
}
