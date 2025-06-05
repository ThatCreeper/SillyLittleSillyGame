#include "CoreWin.h"
#include "CAllocator.h"
#include "CConsole.h"

int main();

extern "C" int _fltused = 0;

unsigned long long gPerfCounterFrequency;

static void SetupPerformanceCounter() {
	QueryPerformanceFrequency(&gPerfCounterFrequency);
	gPerfCounterFrequency /= 1000;
}

// The parameter to this function is unused in the example provided by the Visual C Runtime.
extern "C" int mainCRTStartup(void *) {
	SetLastError(0);

	new(&gAllocator)CAllocator;
	new(&gConsole)CConsole;

	SetupPerformanceCounter();

	int Ret = main();

	CallExitHandlers();

	gConsole.~CConsole();
	gAllocator.~CAllocator();
	
	ExitProcess(Ret);
	return Ret;
}