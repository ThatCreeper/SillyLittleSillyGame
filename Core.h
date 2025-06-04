#pragma once

using HHandle = void *;
using HHeap = void *;
using HConsoleHandle = void *;
using HLibrary = void *;

enum class EHandleType : unsigned int {
	Input = (unsigned int)(-10),
	Output = (unsigned int)(-11),
	Error = (unsigned int)(-12)
};

extern "C" {
	void SetLastError(int Error);
	int GetLastError();
	void ExitProcess(unsigned int ExitCode);

	int CloseHandle(HHandle Handle);

	HHeap GetProcessHeap();
	HHeap HeapCreate(int Options, size_t InitialSize, size_t MaximumSize);
	int HeapDestroy(HHeap Heap);
	HHeap HeapAlloc(HHeap Heap, int Flags, size_t Size);
	int HeapFree(HHeap Heap, int Flags, void *Pointer);

	HConsoleHandle GetStdHandle(EHandleType HandleType);
	int WriteConsoleA(HConsoleHandle Console, const void *Buffer, int Count, int *OutWritten, void *Unused);
	int ReadConsoleA(HConsoleHandle Console, void *OutBuffer, int Count, int *OutRead, void *InputControl);
	int FlushConsoleInputBuffer(HConsoleHandle Console);

	HLibrary LoadLibraryA(const char *FileName);
	int FreeLibrary(HLibrary Library);
	void *GetProcAddress(HLibrary Library, const char *ProcedureName);
}

void Panic();

extern "C" int atexit(void (*ExitHandler)());
void CallExitHandlers();