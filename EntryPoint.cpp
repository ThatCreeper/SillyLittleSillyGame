#include "Core.h"
#include "CUserLib.h"

// Set Break-point Here!
void Panic() {
	Exit(1);
}

int main() {
	CUserLib::Open();

	gUserLib.RegisterClass("WinClass");
	HWindow Window = gUserLib.CreateWindow("WinClass", "Test Window", 500, 500);
	gUserLib.ShowWindow(Window);

	CUserLib::Close();
	return 0;
}