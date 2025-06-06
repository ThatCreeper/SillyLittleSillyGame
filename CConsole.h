#pragma once

#include "Core.h"
#include "CStringView.h"

class CConsole {
public:
	CConsole();
	~CConsole();

	void Write(const char *String, int Length);
	void Write(CStringView String);
	
	template <typename... TRest>
	inline void Write(CStringView First, TRest... Rest) {
		this->Write(First);
		this->Write(Rest...);
	}

	void WriteInteger(int Integer);

	int Read(char *Output, int Size);
	
	void FlushInput();
	void WaitForLine();

protected:
	HConsoleHandle mStdIn = nullptr;
	HConsoleHandle mStdOut = nullptr;
};

extern CConsole gConsole;