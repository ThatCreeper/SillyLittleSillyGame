#pragma once

class CStringView {
public:
	CStringView(const char *String, int Length);
	CStringView(const char *String);

	const char *Data() const;
	int Length() const;
	// Data = null || Length = 0
	bool Invalid() const;

	// WARNING! Returns Length() if no such character exists
	int IndexOfFirstOccurance(char Character) const;

	// Ignores '.'
	int ParseInteger() const;
	// 1000 = 1.000
	float ParseFloat() const;

	CStringView SubString(int Start, int Length) const;
	CStringView Trimmed() const;

private:
	const char *mData;
	int mLength;
};

