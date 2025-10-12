#include "Core.h"
#include "CConsole.h"
#include "CUserLib.h"
#include "CGLLib.h"
#include "CEngine.h"
#include "CStringSplitter.h"
#include "CFile.h"
#include "CAMDCache.h"

void Panic() {
	gConsole.Write("Panic()! Did you set a breakpoint? Last Win Error: ");
	gConsole.WriteInteger(GetWinAPIError());

	// Set break-point here!
	gConsole.WaitForLine();
	Exit(1);
}

int Frame = 0;
unsigned long long lastTime = -1;

int main() {
	CAMDCache AMDCache;

	CEngine Engine;
	Engine.Loop();

	return 0;
}