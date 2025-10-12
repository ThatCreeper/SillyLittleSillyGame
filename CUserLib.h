#pragma once

#include "Core.h"

using HRegisteredClass = unsigned short;
using HWindow = void *;
using HDeviceContext = void *;
using HCursor = void *;

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
	Size = 0x0005,
	Paint = 0x000F,
	EraseBackground = 0x0014,
	KeyDown = 0x0100,
	KeyUp = 0x0101,
	MouseMove = 0x0200,
	LButtonDown = 0x0201,
	LButtonUp = 0x0202,
	RButtonDown = 0x0204,
	RButonUp = 0x0205,
	Sizing = 0x0214,
	DPIChanged = 0x02E0
};
typedef long long (*FWindowProcedure)(HWindow, EMessageKind, long long, long long);

struct SPaintRect {
	int Left;
	int Top;
	int Right;
	int Bottom;
};

struct SPaintStruct {
	HDeviceContext DeviceContext;
	int BackgroundNeedsErasing;
	SPaintRect RequestedArea;
	int PrivateRestore;
	int PrivateIncUpdate;
	char PrivateRGB[32];
};

int LoWord(long long Value);
int HiWord(long long Value);

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
	bool PeekQueuedWindowMessage(SWindowMessage *OutMessage, HWindow Window);
	bool PeekQueuedMessage(SWindowMessage *OutMessage);
	void TranslateVirtualKeyMessages(SWindowMessage *Message);
	long long CallRelevantWindowProcedure(SWindowMessage *Message);
	void StopMessageQueue();
	void SetWindowSize(HWindow Window, int Width, int Height);

	FWindowProcedure DefaultWindowProcedure();

	HDeviceContext GetWindowDeviceContext(HWindow Window);

	SPaintStruct BeginPainting(HWindow Window);
	void EndPainting(HWindow Window, SPaintStruct *PaintStruct);
	void RequestAnimationFrame(HWindow Window);

	HCursor LoadCursor(int Cursor);

	void MarkProcessDPIAware();
	float GetWindowScalingFactor(HWindow Window);

private:
	HInstance mInstance;
	HLibrary mUserLib;

	HRegisteredClass(*mRegisterClassA)(const SWindowClass *WindowClass);
	FWindowProcedure mDefWindowProcA;
	HInstance(*mCreateWindowExA)(int, const char *, const char *, int, int, int, int, int, HWindow, void *, HInstance, void *);
	int (*mShowWindow)(HInstance, int);
	int (*mGetMessageA)(SWindowMessage *, HWindow, unsigned int, unsigned int);
	int (*mPeekMessageA)(SWindowMessage *, HWindow, unsigned int, unsigned int, unsigned int);
	int (*mTranslateMessage)(SWindowMessage *);
	long long (*mDispatchMessageA)(SWindowMessage *);
	void (*mPostQuitMessage)(int);
	HDeviceContext(*mGetDC)(HWindow);
	HDeviceContext(*mBeginPaint)(HWindow, SPaintStruct *);
	int (*mEndPaint)(HWindow, SPaintStruct *);
	int (*mInvalidateRect)(HWindow, SPaintRect *, int);
	int (*mSetWindowPos)(HWindow, HWindow, int, int, int, int, unsigned int);
	int (*mAdjustWindowRectExForDpi)(SPaintRect *, unsigned int, int, unsigned int, unsigned int);
	HCursor(*mLoadCursorA)(HInstance, const char *);
	HCursor(*mSetCursor)(HCursor);
	int (*mSetProcessDpiAwarenessContext)(int);
	unsigned int (*mGetDpiForWindow)(HWindow);
};

extern CUserLib gUserLib;
