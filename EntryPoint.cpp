#include "Core.h"
#include "CConsole.h"
#include "CUserLib.h"

// Set Break-point Here!
void Panic() {
	gConsole.Write("Panic()! Did you set a breakpoint?");
	Exit(1);
}

long long WindowProcedure(HWindow Window, EMessageKind MessageKind, long long WParam, long long LParam) {
	switch (MessageKind) {
	case EMessageKind::Destroyed:
		gUserLib.StopMessageQueue();
		return 0;
	}
	return gUserLib.DefaultWindowProcedure()(Window, MessageKind, WParam, LParam);
}

int main() {
	CUserLib::Open();

	gUserLib.RegisterClass("WinClass", WindowProcedure);
	HWindow Window = gUserLib.CreateWindow("WinClass", "Test Window", 500, 500);
	gUserLib.ShowWindow(Window);

	SWindowMessage WindowMessage;
	while (gUserLib.PopQueuedMessage(&WindowMessage)) {
		gUserLib.TranslateVirtualKeyMessages(&WindowMessage);
		gUserLib.CallRelevantWindowProcedure(&WindowMessage);
	}

	CUserLib::Close();
	return 0;
}