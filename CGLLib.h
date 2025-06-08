#pragma once

#include "CUserLib.h"

using HGLContext = void *;

enum class EClearBuffer : int {
	Color = 0x00004000,
	Depth = 0x00000100,
	Accumulator = 0x00000200,
	Stencil = 0x00000400
};

enum class EGLEnable : int {
	StencilTest = 0x0B90,
	Blending = 0x0BE2,
	ScissorTest = 0x0C11
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
	void PushTransformMatrix();
	void PopTransformMatrix();
	void ScaleTransform(float X, float Y, float Z);
	void TranslateTransform(float X, float Y, float Z);
	void ColoredVertex(float X, float Y, float R, float G, float B, float A);
	void BeginTriangles();
	void BeginQuads();
	void BeginTriangleStrip();
	void EndDrawing();
	void SetViewport(int Width, int Height);
	void StartScissor(int X, int Y, int Width, int Height);
	void EndScissor();

	void RequestSanePixelFormat(HDeviceContext DeviceContext);
	void EnableVSync();
	void EnableTransparency();

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
	void (*mglEnable)(EGLEnable);
	void (*mglStencilFunc)(int, int, unsigned int);
	void (*mglStencilOp)(int, int, int);
	void (*mglStencilMask)(unsigned int);
	void (*mglVertex2f)(float, float);
	void (*mglColor4f)(float, float, float, float);
	void (*mglBlendFunc)(int, int);
	void (*mglPushMatrix)();
	void (*mglPopMatrix)();
	void (*mglScalef)(float, float, float);
	void (*mglBegin)(int);
	void (*mglEnd)();
	void (*mglTranslatef)(float, float, float);
	void (*mglViewport)(int, int, int, int);
	void (*mglScissor)(int, int, int, int);
	void (*mglDisable)(EGLEnable);

	void (*mwglSwapIntervalEXT)(int);
};

extern CGLLib gGLLib;