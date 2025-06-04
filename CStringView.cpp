#include "CStringView.h"

static int ZeroTerminatedStringLength(const char *String) {
	int Length = 0;
	while (*(String++) != '\0')
		Length++;
	return Length;
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
