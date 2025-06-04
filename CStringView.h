#pragma once

class CStringView {
public:
	CStringView(const char *String, int Length);
	CStringView(const char *String);

	const char *Data() const;
	int Length() const;

	int ParseInteger() const;

	CStringView SubString(int Start, int Length) const;
	CStringView Trimmed() const;

private:
	const char *mData;
	int mLength;
};

