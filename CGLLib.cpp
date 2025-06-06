#include "CGLLib.h"

#include "CoreWin.h"
#include "CAllocator.h"

CGLLib gGLLib;

CGLLib::CGLLib()
{
	this->mGDILib = LoadLibraryA("gdi32.dll");

	// See CUserLib.cpp for a descriptive comment
#define LOAD_GDI(Name) *((void **)(&this->m##Name)) = (void *)GetProcAddress(this->mGDILib, #Name); if (!this->m##Name) Panic()

	LOAD_GDI(ChoosePixelFormat);
	LOAD_GDI(SetPixelFormat);

#undef LOAD_GDI

	this->mGLLib = LoadLibraryA("opengl32.dll");

	// See CUserLib.cpp for a descriptive comment
#define LOAD_GL(Name) *((void **)(&this->m##Name)) = (void *)GetProcAddress(this->mGLLib, #Name); if (!this->m##Name) Panic()

	LOAD_GL(wglCreateContext);
	LOAD_GL(wglDeleteContext);
	LOAD_GL(wglMakeCurrent);
	LOAD_GL(wglGetProcAddress);
	LOAD_GL(wglSwapLayerBuffers);

	LOAD_GL(glClearColor);
	LOAD_GL(glClear);
	LOAD_GL(glFlush);

#undef LOAD_GL

	this->mwglSwapIntervalEXT = nullptr;
}

CGLLib::~CGLLib()
{
	FreeLibrary(this->mGLLib);
	FreeLibrary(this->mGDILib);
}

void CGLLib::Open()
{
	new(&gGLLib)CGLLib;
}

void CGLLib::Close()
{
	gGLLib.~CGLLib();
}

void CGLLib::LoadExtensions()
{
	// See CUserLib.cpp for a descriptive comment
#define LOAD_EXT(Name) *((void **)(&this->m##Name)) = (void *)this->mwglGetProcAddress(#Name); if (!this->m##Name) Panic()

	LOAD_EXT(wglSwapIntervalEXT);

#undef LOAD_EXT
}

HGLContext CGLLib::MakeGLContext(HDeviceContext DeviceContext)
{
	return this->mwglCreateContext(DeviceContext);
}

void CGLLib::DestroyGLContext(HGLContext GLContext)
{
	this->mwglDeleteContext(GLContext);
}

void CGLLib::MakeContextCurrent(HDeviceContext DeviceContext, HGLContext GLContext)
{
	this->mwglMakeCurrent(DeviceContext, GLContext);
}

void CGLLib::SetClearColor(float Red, float Green, float Blue, float Alpha)
{
	this->mglClearColor(Red, Green, Blue, Alpha);
}

void CGLLib::ClearBuffers(EClearBuffer Buffers)
{
	this->mglClear(Buffers);
}

void CGLLib::Flush()
{
	this->mglFlush();
}

void CGLLib::SwapBuffers(HDeviceContext DeviceContext)
{
	this->mwglSwapLayerBuffers(DeviceContext, 1 /* Main Plane */);
}

enum class EPixelFormatFlags : int {
	DrawToWindow = 0x00000004,
	SupportOpenGL = 0x00000020,
	DoubleBuffered = 0x00000001
};
inline EPixelFormatFlags operator|(EPixelFormatFlags A, EPixelFormatFlags B) {
	return (EPixelFormatFlags)((int)A | (int)B);
}

enum class EPixelType : char {
	RGBA = 0,
	ColorIndexed = 1
};

struct SPixelFormat {
	short Size;
	short Version;
	EPixelFormatFlags Flags;
	EPixelType PixelType;
	char ColorBits;
	char RedBits;
	char RedShift;
	char GreenBits;
	char GreenShift;
	char BlueBits;
	char BlueShift;
	char AlphaBits;
	char AlphaShift;
	char AccumulatorBits;
	char AccumulatorRedBits;
	char AccumulatorGreenBits;
	char AccumulatorBlueBits;
	char AccumulatorAlphaBits;
	char DepthBits;
	char StencilBits;
	char AuxBuffers;
	char LayerType;
	char Private;
	int LayerMask;
	int VisibleMask;
	int DamageMask;
};

void CGLLib::RequestSanePixelFormat(HDeviceContext DeviceContext)
{
	SPixelFormat PixelFormat = { 0 };
	PixelFormat.Size = sizeof(SPixelFormat);
	PixelFormat.Version = 1;
	PixelFormat.Flags = EPixelFormatFlags::DrawToWindow | EPixelFormatFlags::SupportOpenGL;
	PixelFormat.PixelType = EPixelType::RGBA;
	PixelFormat.ColorBits = 32;
	PixelFormat.AlphaBits = 8;
	PixelFormat.DepthBits = 24;

	int DecidedFormat = this->mChoosePixelFormat(DeviceContext, &PixelFormat);
	this->mSetPixelFormat(DeviceContext, DecidedFormat, &PixelFormat);
}

void CGLLib::EnableVSync()
{
	this->mwglSwapIntervalEXT(1 /* VSYNC */);
}
