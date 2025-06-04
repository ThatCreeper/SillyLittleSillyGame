#include "CoreWin.h"
#include "CAllocator.h"
#include "CConsole.h"

int main();

// The parameter to this function is unused in the example provided by the Visual C Runtime.
extern "C" int mainCRTStartup(void *) {
	new(&gAllocator)CAllocator;
	new(&gConsole)CConsole;

	int Ret = main();

	CallExitHandlers();

	gConsole.~CConsole();
	gAllocator.~CAllocator();
	ExitProcess(Ret);
	return Ret;
}