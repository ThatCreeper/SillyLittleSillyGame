#pragma once

#include "CUserLib.h"
#include "CGLLib.h"

class CEngine
{
public:
	CEngine();
	~CEngine();

	void Loop();

	void Frame();

protected:
	float GetDeltaTime();

	HWindow mWindow;
	HDeviceContext mDeviceContext;
	HGLContext mGLContext;
	unsigned long long mLastTime;
	float mRed = 0;
};

