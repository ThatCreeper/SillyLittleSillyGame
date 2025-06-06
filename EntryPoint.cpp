#include "Core.h"
#include "CConsole.h"
#include "CUserLib.h"
#include "CGLLib.h"
#include "CGlobalResource.h"
#include "CEngine.h"
#include "CStringSplitter.h"

[[noreturn]] void Panic() {
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

	//CEngine Engine;
	//Engine.Loop();

	CStringSplitter Splitter("Hello\nWorld!\n\n1\n", '\n');
	for (;;) {
		CStringView Segment = Splitter.ReadString();
		if (Segment.Invalid()) {
			gConsole.Write("Invalid segment!\n");
			break;
		}
		CStringView Trimmed = Segment.Trimmed();
		if (Trimmed.Invalid()) {
			gConsole.Write("SEG<EMPTY>\n");
			continue;
		}
		gConsole.Write("SEG\"");
		gConsole.Write(Trimmed);
		gConsole.Write("\"\n");
	}

	gConsole.WaitForLine();

	return 0;
}