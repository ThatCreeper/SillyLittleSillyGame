#include "Core.h"
#include "CAllocator.h"
#include "CConsole.h"

int main();

static void Pause() {
	gConsole.Write("Press [Enter] to close window.\n");
	gConsole.WaitForLine();
}

// The parameter to this function is unused in the example provided by the Visual C Runtime.
extern "C" int mainCRTStartup(void *) {
	new(&gAllocator)CAllocator;
	new(&gConsole)CConsole;

	int Ret = main();

	CallExitHandlers();
	Pause();

	gConsole.~CConsole();
	gAllocator.~CAllocator();
	ExitProcess(Ret);
	return Ret;
}