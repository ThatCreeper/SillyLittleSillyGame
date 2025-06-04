#include "Core.h"
#include "CUserLib.h"

// Set Break-point Here!
void Panic() {
	ExitProcess(1);
}

int main() {
	CUserLib::Open();



	CUserLib::Close();
	return 0;
}