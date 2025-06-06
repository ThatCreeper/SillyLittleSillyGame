#include "Core.h"

#include "CoreWin.h"

// Standards-compliant
static void (*gExitHandlers[32])();
static int gcExitHandlers = 0;

extern "C" int atexit(void (*ExitHandler)()) {
	if (gcExitHandlers >= 32)
		return 1;
	gExitHandlers[gcExitHandlers++] = ExitHandler;
	return 0;
}

void CallExitHandlers() {
	for (int i = 0; i < gcExitHandlers; i++) {
		gExitHandlers[i]();
	}
}

void Exit(int ExitCode) {
	CallExitHandlers();
	ExitProcess(ExitCode);
}

int GetWinAPIError()
{
	return GetLastError();
}

extern unsigned long long gPerfCounterFrequency;

unsigned long long GetTimeMilliseconds()
{
	unsigned long long Counts;
	QueryPerformanceCounter(&Counts);
	Counts /= gPerfCounterFrequency;
	return Counts;
}

int Pow(int Number, int Exponent)
{
	if (Exponent < 0)
		return 0;

	int Return = 1;
	
	while (Exponent--) {
		Return *= Number;
	}

	return Return;
}
