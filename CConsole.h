#pragma once

#include "Core.h"
#include "CStringView.h"

class CConsole {
public:
	CConsole();
	~CConsole();

	void Write(const char *String, int Length);
	void Write(CStringView String);
	int Read(char *Output, int Size);
	
	void FlushInput();
	void WaitForLine();

protected:
	HConsoleHandle mStdIn = nullptr;
	HConsoleHandle mStdOut = nullptr;
};

extern CConsole gConsole;