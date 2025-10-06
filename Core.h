#pragma once

using HHandle = void *;
using HHeap = void *;
using HConsoleHandle = void *;
using HLibrary = void *;
using HInstance = void *;
using HFile = void *;

enum class EHandleType : unsigned int {
	Input = (unsigned int)(-10),
	Output = (unsigned int)(-11),
	Error = (unsigned int)(-12)
};

_declspec(noreturn) void Panic();
inline _declspec(noreturn) void Assert(bool MustBeTrue) {
	if (!MustBeTrue) Panic();
}

extern "C" int atexit(void (*ExitHandler)());
void CallExitHandlers();

void Exit(int ExitCode);
int GetWinAPIError();
unsigned long long GetTimeMilliseconds();

int Pow(int Number, int Exponent);