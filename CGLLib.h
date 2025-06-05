#pragma once

#include "CUserLib.h"

using HGLContext = void *;

enum class EClearBuffer : int {
	Color = 0x00004000,
	Depth = 0x00000100,
	Accumulator = 0x00000200,
	Stencil = 0x00000400
};

class CGLLib
{
public:
	CGLLib();
	~CGLLib();

	static void Open();
	static void Close();

	void LoadExtensions();

	HGLContext MakeGLContext(HDeviceContext DeviceContext);
	void DestroyGLContext(HGLContext GLContext);
	void MakeContextCurrent(HDeviceContext DeviceContext, HGLContext GLContext);

	void SetClearColor(float Red, float Green, float Blue, float Alpha);
	void ClearBuffers(EClearBuffer Buffers);
	void Flush();
	void SwapBuffers(HDeviceContext DeviceContext);

	void RequestSanePixelFormat(HDeviceContext DeviceContext);
	void EnableVSync();

protected:
	HLibrary mGDILib;
	HLibrary mGLLib;

	int (*mChoosePixelFormat)(HDeviceContext, void *);
	int (*mSetPixelFormat)(HDeviceContext, int, void *);

	HGLContext(*mwglCreateContext)(HDeviceContext);
	int (*mwglDeleteContext)(HGLContext);
	int (*mwglMakeCurrent)(HDeviceContext, HGLContext);
	int (*mwglSwapLayerBuffers)(HDeviceContext, unsigned int);
	void *(*mwglGetProcAddress)(const char *);

	void (*mglClearColor)(float, float, float, float);
	void (*mglClear)(EClearBuffer);
	void (*mglFlush)();

	void (*mwglSwapIntervalEXT)(int);
};

extern CGLLib gGLLib;