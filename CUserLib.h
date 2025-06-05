#pragma once

#include "Core.h"

using HRegisteredClass = unsigned short;
using HWindow = void *;
using HDeviceContext = void *;

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
	Destroyed = 0x0002,
	Paint = 0x000F
};
typedef long long (*FWindowProcedure)(HWindow, EMessageKind, long long, long long);

struct SPaintRect {
	int left;
	int top;
	int right;
	int bottom;
};

struct SPaintStruct {
	HDeviceContext DeviceContext;
	int BackgroundNeedsErasing;
	SPaintRect RequestedArea;
	int PrivateRestore;
	int PrivateIncUpdate;
	char PrivateRGB[32];
};

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

	HDeviceContext GetWindowDeviceContext(HWindow Window);

	SPaintStruct BeginPainting(HWindow Window);
	void EndPainting(HWindow Window, SPaintStruct *PaintStruct);
	void RequestAnimationFrame(HWindow Window);

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
	HDeviceContext(*mGetDC)(HWindow);
	HDeviceContext(*mBeginPaint)(HWindow, SPaintStruct *);
	int (*mEndPaint)(HWindow, SPaintStruct *);
	int (*mInvalidateRect)(HWindow, SPaintRect *, int);
};

extern CUserLib gUserLib;
