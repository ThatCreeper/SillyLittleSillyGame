#pragma once

#include "CUserLib.h"
#include "CGLLib.h"

class CGame;

class CEngine
{
public:
	CEngine();
	~CEngine();

	void Loop();

	void Frame();

	int Width();
	int Height();

protected:
	float GetDeltaTime();

	HWindow mWindow;
	HDeviceContext mDeviceContext;
	HGLContext mGLContext;
	unsigned long long mLastTime;
	CGame *mGame;
	int mWindowWidth = 800;
	int mWindowHeight = 600;

	friend long long WindowProcedure(HWindow Window, EMessageKind MessageKind, long long WParam, long long LParam);;
};

