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

	// Rendering Dimensions
	int Width();
	int Height();

	int ScalingFactor();
	int RealWidth();
	int RealHeight();

protected:
	float GetDeltaTime();
	void UpdateDPI();
	void UpdateProjection();

	HWindow mWindow;
	HDeviceContext mDeviceContext;
	HGLContext mGLContext;
	unsigned long long mLastTime;
	CGame *mGame;
	int mWindowWidth = 800;
	int mWindowHeight = 600;
	int mScalingFactor = 1;
	int mWindowRealWidth = 800;
	int mWindowRealHeight = 600;

	friend long long WindowProcedure(HWindow Window, EMessageKind MessageKind, long long WParam, long long LParam);;
};

