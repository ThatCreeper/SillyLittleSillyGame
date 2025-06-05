#include "CoreWin.h"
#include "CAllocator.h"
#include "CConsole.h"

int main();

extern "C" int _fltused = 0;

// The parameter to this function is unused in the example provided by the Visual C Runtime.
extern "C" int mainCRTStartup(void *) {
	SetLastError(0);

	new(&gAllocator)CAllocator;
	new(&gConsole)CConsole;

	int Ret = main();

	CallExitHandlers();

	gConsole.~CConsole();
	gAllocator.~CAllocator();
	ExitProcess(Ret);
	return Ret;
}