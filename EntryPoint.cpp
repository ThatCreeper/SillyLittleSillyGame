#include "Core.h"
#include "CConsole.h"
#include "CUserLib.h"
#include "CGLLib.h"
#include "CGlobalResource.h"
#include "CEngine.h"
#include "CStringSplitter.h"
#include "CFile.h"

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
	CGlobalResource<CUserLib> UserRAII;
	CGlobalResource<CGLLib> GLRAII;

	CEngine Engine("Demo");
	Engine.Loop();

	return 0;
}