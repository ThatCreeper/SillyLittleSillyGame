#pragma once

#include "CStringView.h"
#include "CStringSplitter.h"

class CLevelReader {
public:
	CLevelReader(CStringView Data);

	CStringView Line();

	int Int();
	float Float();

protected:
	CStringSplitter mSplitter;
};