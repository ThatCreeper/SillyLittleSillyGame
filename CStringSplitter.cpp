#include "CStringSplitter.h"
#include "Core.h"

CStringSplitter::CStringSplitter(CStringView StringView, char SplitCharacter)
	: mStringView(StringView)
	, mSplitCharacter(SplitCharacter)
{
}

CStringView CStringSplitter::ReadString()
{
	int Position = this->mStringView.IndexOfFirstOccurance(this->mSplitCharacter);
	CStringView First = this->mStringView.SubString(0, Position + 1);
	this->mStringView = this->mStringView.SubString(Position + 1, this->mStringView.Length());
	return First;
}

CStringView CStringSplitter::PeakString()
{
	int Position = this->mStringView.IndexOfFirstOccurance(this->mSplitCharacter);
	return this->mStringView.SubString(0, Position + 1);
}

CStringView CStringSplitter::ReadNonEmptyString()
{
	Panic();
	return CStringView(nullptr, 0);
}
