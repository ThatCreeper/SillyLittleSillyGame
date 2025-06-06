#pragma once

#include "Core.h"

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
	void *HeapReAlloc(HHeap Heap, int Flags, void *Memory, size_t Size);

	HConsoleHandle GetStdHandle(EHandleType HandleType);
	int WriteConsoleA(HConsoleHandle Console, const void *Buffer, int Count, int *OutWritten, void *Unused);
	int ReadConsoleA(HConsoleHandle Console, void *OutBuffer, int Count, int *OutRead, void *InputControl);
	int FlushConsoleInputBuffer(HConsoleHandle Console);

	HLibrary LoadLibraryA(const char *FileName);
	int FreeLibrary(HLibrary Library);
	void *GetProcAddress(HLibrary Library, const char *ProcedureName);

	HInstance GetModuleHandleA(const char *ModuleName);

	int QueryPerformanceCounter(unsigned long long *OutCounts);
	int QueryPerformanceFrequency(unsigned long long *OutFrequency);

	void *CreateThread(void *SecurityAttributes, size_t StackSize, int (*Function)(void *), void *User, int Flags, int *OutThreadId);
	void Sleep(int Milliseconds);
	int Beep(int Frequency, int Milliseconds);

	HFile CreateFileA(const char *FileName, int Permission, int SharedPermission, void *HandleSecurity, int Command, int FileAttributes, HFile TemplatePermissions);
	int GetFileSizeEx(HFile File, unsigned long long *OutSize);
	int ReadFile(HFile File, void *OutBuffer, int Count, int *OutRead, void *OverlappedStructure);
}