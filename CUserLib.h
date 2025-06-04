#pragma once

#include "Core.h"

using HRegisteredClass = unsigned short;
using HWindow = void *;

struct SWindowClass;

struct SMousePoint {
	int X;
	int Y;
};

struct SWindowMessage {
	HWindow Window;
	unsigned int MessageKind;
	long long WParam;
	long long LParam;
	long long Time;
	SMousePoint MouseLocation;
	long long Private;
};

enum class EMessageKind : unsigned int {
	Destroyed = 0x0002
};
typedef long long (*FWindowProcedure)(HWindow, EMessageKind, long long, long long);

class CUserLib {
public:
	CUserLib();
	~CUserLib();

	static void Open();
	static void Close();

	HInstance GetInstance();

	void RegisterClass(const char *ClassName, FWindowProcedure WindowProcedure);
	HWindow CreateWindow(const char *ClassName, const char *WindowName, int Width, int Height);

	void ShowWindow(HWindow Window);

	bool PopQueuedWindowMessage(SWindowMessage *OutMessage, HWindow Window);
	bool PopQueuedMessage(SWindowMessage *OutMessage);
	void TranslateVirtualKeyMessages(SWindowMessage *Message);
	long long CallRelevantWindowProcedure(SWindowMessage *Message);
	void StopMessageQueue();

	FWindowProcedure DefaultWindowProcedure();

private:
	HInstance mInstance;
	HLibrary mUserLib;

	HRegisteredClass(*mRegisterClassA)(const SWindowClass *WindowClass);
	FWindowProcedure mDefWindowProcA;
	HInstance(*mCreateWindowExA)(int, const char *, const char *, int, int, int, int, int, HWindow, void *, HInstance, void *);
	int (*mShowWindow)(HInstance, int);
	int (*mGetMessageA)(SWindowMessage *, HWindow, unsigned int, unsigned int);
	int (*mTranslateMessage)(SWindowMessage *);
	long long (*mDispatchMessageA)(SWindowMessage *);
	void (*mPostQuitMessage)(int);
};

extern CUserLib gUserLib;
