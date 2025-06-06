#pragma once

#include "CStringView.h"

class CStringSplitter
{
public:
	CStringSplitter(CStringView StringView, char SplitCharacter);
	
	CStringView ReadString();
	CStringView PeakString();
	CStringView ReadNonEmptyString();

protected:
	CStringView mStringView;
	char mSplitCharacter;
};

