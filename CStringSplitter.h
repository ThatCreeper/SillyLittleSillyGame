#pragma once

#include "CStringView.h"

class CStringSplitter
{
public:
	CStringSplitter(CStringView StringView, char SplitCharacter);
	
	CStringView ReadString();
	CStringView PeakString();
	CStringView ReadNonEmptyString();

	CStringView NextLineNoComment(char CommentCharacter);

protected:
	CStringView mStringView;
	char mSplitCharacter;
};

