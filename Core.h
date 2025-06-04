#pragma once

using HHandle = void *;
using HHeap = void *;
using HConsoleHandle = void *;
using HLibrary = void *;
using HInstance = void *;

enum class EHandleType : unsigned int {
	Input = (unsigned int)(-10),
	Output = (unsigned int)(-11),
	Error = (unsigned int)(-12)
};

void Panic();

extern "C" int atexit(void (*ExitHandler)());
void CallExitHandlers();

void Exit(int ExitCode);

int Pow(int Number, int Exponent);