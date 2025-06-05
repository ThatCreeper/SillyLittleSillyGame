#include "CConsole.h"

#include "CoreWin.h"
#include "CString.h"

CConsole gConsole;

CConsole::CConsole() {
	this->mStdIn = GetStdHandle(EHandleType::Input);
	this->mStdOut = GetStdHandle(EHandleType::Output);
}

CConsole::~CConsole() {
	CloseHandle(this->mStdOut);
	CloseHandle(this->mStdIn);
}

void CConsole::Write(const char *String, int Length) {
	if (!this->mStdOut)
		return;
	int Written;
	WriteConsoleA(this->mStdOut, String, Length, &Written, nullptr);
}

void CConsole::Write(CStringView String) {
	this->Write(String.Data(), String.Length());
}

void CConsole::WriteInteger(int Integer)
{
	CString String;
	String.AddInteger(Integer);
	this->Write(String.View());
}

int CConsole::Read(char *Output, int Size) {
	if (!this->mStdIn)
		return 0;
	if (Size <= 3)
		return 0;
	int Read = 0;
	ReadConsoleA(this->mStdIn, Output, Size - 3, &Read, nullptr);
	Output[Read - 2] = '\r';
	Output[Read - 1] = '\n';
	Output[Read - 0] = '\0';
	return Read;
}

void CConsole::FlushInput() {
	FlushConsoleInputBuffer(this->mStdIn);
}

void CConsole::WaitForLine() {
	this->FlushInput();
	char Output[4];
	this->Read(Output, 4);
}
