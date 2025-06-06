#pragma once

#include "CUserLib.h"
#include "CGLLib.h"
#include "CLevel.h"

class CEngine
{
public:
	CEngine(CStringView LevelName);
	~CEngine();

	void Loop();

	void Frame();

protected:
	float GetDeltaTime();

	HWindow mWindow;
	HDeviceContext mDeviceContext;
	HGLContext mGLContext;
	unsigned long long mLastTime;
	CLevel *mLevel;
};

