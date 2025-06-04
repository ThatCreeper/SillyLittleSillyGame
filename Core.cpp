#include "Core.h"

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
