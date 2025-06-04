#pragma once

#include "Core.h"

using HRegisteredClass = unsigned short;
using HWindow = void *;

struct SWindowClass;

class CUserLib {
public:
	CUserLib();
	~CUserLib();

	static void Open();
	static void Close();

	HInstance GetInstance();

	void RegisterClass(const char *ClassName);
	HWindow CreateWindow(const char *ClassName, const char *WindowName, int Width, int Height);

	void ShowWindow(HWindow Window);

private:
	HInstance mInstance;
	HLibrary mUserLib;

	HRegisteredClass(*mRegisterClassA)(const SWindowClass *WindowClass);
	long long (*mDefWindowProcA)(HWindow, unsigned int, unsigned long long, long long);
	HInstance(*mCreateWindowExA)(int, const char *, const char *, int, int, int, int, int, HWindow, void *, HInstance, void *);
	int (*mShowWindow)(HInstance, int);
};

extern CUserLib gUserLib;
