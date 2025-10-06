#include "CGLLib.h"

#include "CoreWin.h"
#include "CAllocator.h"

CGLLib gGLLib;

CGLLib::CGLLib()
{
	this->mGDILib = LoadLibraryA("gdi32.dll");

	// See CUserLib.cpp for a descriptive comment
#define LOAD_GDI(Name) *((void **)(&this->m##Name)) = (void *)GetProcAddress(this->mGDILib, #Name); Assert(this->m##Name)

	LOAD_GDI(ChoosePixelFormat);
	LOAD_GDI(SetPixelFormat);

#undef LOAD_GDI

	this->mGLLib = LoadLibraryA("opengl32.dll");

	// See CUserLib.cpp for a descriptive comment
#define LOAD_GL(Name) *((void **)(&this->m##Name)) = (void *)GetProcAddress(this->mGLLib, #Name); Assert(this->m##Name)

	LOAD_GL(wglCreateContext);
	LOAD_GL(wglDeleteContext);
	LOAD_GL(wglMakeCurrent);
	LOAD_GL(wglGetProcAddress);
	LOAD_GL(wglSwapLayerBuffers);

	LOAD_GL(glClearColor);
	LOAD_GL(glClear);
	LOAD_GL(glFlush);
	LOAD_GL(glEnable);
	LOAD_GL(glStencilFunc);
	LOAD_GL(glStencilMask);
	LOAD_GL(glStencilOp);
	LOAD_GL(glBlendFunc);
	LOAD_GL(glVertex2f);
	LOAD_GL(glVertex2i);
	LOAD_GL(glColor4f);
	LOAD_GL(glPushMatrix);
	LOAD_GL(glPopMatrix);
	LOAD_GL(glScalef);
	LOAD_GL(glBegin);
	LOAD_GL(glEnd);
	LOAD_GL(glTranslatef);
	LOAD_GL(glViewport);
	LOAD_GL(glScissor);
	LOAD_GL(glDisable);
	LOAD_GL(glMatrixMode);
	LOAD_GL(glLoadIdentity);
	LOAD_GL(glOrtho);

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
#define LOAD_EXT(Name) *((void **)(&this->m##Name)) = (void *)this->mwglGetProcAddress(#Name); Assert(this->m##Name)

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

void CGLLib::PushTransformMatrix()
{
	this->mglPushMatrix();
}

void CGLLib::PopTransformMatrix()
{
	this->mglPopMatrix();
}

void CGLLib::ScaleTransform(float X, float Y, float Z)
{
	this->mglScalef(X, Y, Z);
}

void CGLLib::TranslateTransform(float X, float Y, float Z)
{
	this->mglTranslatef(X, Y, Z);
}

void CGLLib::ColoredVertex(float X, float Y, float R, float G, float B, float A)
{
	this->mglColor4f(R, G, B, A);
	this->mglVertex2f(X, Y);
}

void CGLLib::VertexColor(float R, float G, float B, float A)
{
	this->mglColor4f(R, G, B, A);
}

void CGLLib::IntVertex(int X, int Y)
{
	this->mglVertex2i(X, Y);
}

void CGLLib::BeginTriangles()
{
	int Triangles = 0x0004;
	this->mglBegin(Triangles);
}

void CGLLib::BeginQuads()
{
	int Quads = 0x0007;
	this->mglBegin(Quads);
}

void CGLLib::BeginTriangleStrip()
{
	int TriangleStrip = 0x0005;
	this->mglBegin(TriangleStrip);
}

void CGLLib::EndDrawing()
{
	this->mglEnd();
}

void CGLLib::SetViewport(int Width, int Height)
{
	this->mglViewport(0, 0, Width, Height);
}

void CGLLib::StartScissor(int X, int Y, int Width, int Height)
{
	this->mglScissor(X, Y, Width, Height);
	this->mglEnable(EGLEnable::ScissorTest);
}

void CGLLib::EndScissor()
{
	this->mglDisable(EGLEnable::ScissorTest);
}

void CGLLib::SetMatrixMode(EMatrixMode Mode)
{
	this->mglMatrixMode(Mode);
}

void CGLLib::LoadIdentityMatrix()
{
	this->mglLoadIdentity();
}

void CGLLib::OrthoMatrix(double Left, double Right, double Bottom, double Top, double Near, double Far)
{
	this->mglOrtho(Left, Right, Bottom, Top, Near, Far);
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

void CGLLib::EnableTransparency()
{
	int SourceAlpha = 0x0302;
	int OneMinusSourceAlpha = 0x0303;

	this->mglEnable(EGLEnable::Blending);
	this->mglBlendFunc(SourceAlpha, OneMinusSourceAlpha);
}
