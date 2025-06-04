#pragma once

class CStringView {
public:
	CStringView(const char *String);

	const char *Data() const;
	int Length() const;

private:
	const char *mData;
	int mLength;
};

