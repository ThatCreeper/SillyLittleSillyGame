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
	ScissorTest = 0x0C11,
	Texture2D = 0x0DE1
};

enum class EMatrixMode : int {
	ModelView = 0x1700,
	Projection = 0x1701,
	Texture = 0x1702,
	Color = 0x1800
};

enum class ETextureTarget : int {
	Texture2D = 0x0DE1
};

enum class EInternalFormat : int {
	RGBA8 = 0x8058
};

enum class EFormat : int {
	RGBA = 0x1908
};

enum class EPixelType : int {
	UnsignedByte = 0x1401
};

struct SGLTextureHandle {
	unsigned int Handle;
};

typedef void (*FDebugCallback)(int, int, unsigned int, int, int, const char *, const void *);

class CGLLib
{
public:
	CGLLib();
	~CGLLib();

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
	void VertexColor(float R, float G, float B, float A);
	void TextureCoordinate(float X, float Y);
	void IntVertex(int X, int Y);
	void BeginTriangles();
	void BeginQuads();
	void BeginTriangleStrip();
	void EndDrawing();
	void SetViewport(int Width, int Height);
	void StartScissor(int X, int Y, int Width, int Height);
	void EndScissor();
	void SetMatrixMode(EMatrixMode Mode);
	void LoadIdentityMatrix();
	void OrthoMatrix(double Left, double Right, double Bottom, double Top, double Near, double Far);
	SGLTextureHandle CreateTexture();
	void DestroyTexture(SGLTextureHandle Handle);
	void BindTexture(ETextureTarget Target, SGLTextureHandle Handle);
	void UploadTexture(ETextureTarget Target, int Width, int Height, EInternalFormat InternalFormat, EFormat Format, EPixelType PixelType, const void *Data);
	void EnableTexture();
	void DisableTexture();
	void CopyPixelBuffer(int X, int Y, int Width, int Height, const void *Data);

	void RequestSanePixelFormat(HDeviceContext DeviceContext);
	void EnableVSync();
	void EnableTransparency();
	void SetDebugCallback(FDebugCallback Callback);
	int GetLastError();

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
	void (*mglVertex2i)(int, int);
	void (*mglColor4f)(float, float, float, float);
	void (*mglTexCoord2f)(float, float);
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
	void (*mglMatrixMode)(EMatrixMode);
	void (*mglLoadIdentity)();
	void (*mglOrtho)(double, double, double, double, double, double);
	void (*mglGenTextures)(int, SGLTextureHandle *);
	void (*mglTexImage2D)(ETextureTarget, int, EInternalFormat, int, int, int, EFormat, EPixelType, const void *);
	void (*mglBindTexture)(ETextureTarget, SGLTextureHandle);
	void (*mglDeleteTextures)(int, const SGLTextureHandle *);
	void (*mglDrawPixels)(int, int, EFormat, EPixelType, const void *);
	void (*mglRasterPos2i)(int, int);
	int (*mglGetError)();

	void (*mwglSwapIntervalEXT)(int);
	void (*mglDebugMessageCallback)(FDebugCallback, const void *);
};

extern CGLLib gGLLib;