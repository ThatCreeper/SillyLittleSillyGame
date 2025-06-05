#include "CEngine.h"

static CEngine *gEngineSingleton;

long long WindowProcedure(HWindow Window, EMessageKind MessageKind, long long WParam, long long LParam) {
	switch (MessageKind) {
	case EMessageKind::Paint:
		gEngineSingleton->Frame();
		return 0;
	case EMessageKind::Destroyed:
		gUserLib.StopMessageQueue();
		return 0;
	}
	return gUserLib.DefaultWindowProcedure()(Window, MessageKind, WParam, LParam);
}

CEngine::CEngine()
{
	gEngineSingleton = this;

	gUserLib.RegisterClass("WinClass", WindowProcedure);
	this->mWindow = gUserLib.CreateWindow("WinClass", "Test Window", 500, 500);

	// These are leaked because I frankly don't want to deal with them properly
	this->mDeviceContext = gUserLib.GetWindowDeviceContext(this->mWindow);

	gGLLib.RequestSanePixelFormat(this->mDeviceContext);

	this->mGLContext = gGLLib.MakeGLContext(this->mDeviceContext);
	gGLLib.MakeContextCurrent(this->mDeviceContext, this->mGLContext);

	gGLLib.LoadExtensions();
	gGLLib.EnableVSync();

	gUserLib.ShowWindow(this->mWindow);

	this->mLastTime = GetTimeMilliseconds();
}

CEngine::~CEngine()
{
	// Leak everything; program is closing
}

void CEngine::Loop()
{
	SWindowMessage WindowMessage;
	while (gUserLib.PopQueuedMessage(&WindowMessage)) {
		gUserLib.TranslateVirtualKeyMessages(&WindowMessage);
		gUserLib.CallRelevantWindowProcedure(&WindowMessage);
	}
}

void CEngine::Frame()
{
	float DeltaTime = this->GetDeltaTime();
	this->mRed += DeltaTime * 0.2f;

	gGLLib.SetClearColor(this->mRed, 0, 1, 1);
	gGLLib.ClearBuffers(EClearBuffer::Color);
	gGLLib.Flush();

	SPaintStruct paint = gUserLib.BeginPainting(this->mWindow);
	gUserLib.EndPainting(this->mWindow, &paint);

	gUserLib.RequestAnimationFrame(this->mWindow);
}

float CEngine::GetDeltaTime()
{
	unsigned long long CurrentTime = GetTimeMilliseconds();
	float DeltaTime = (float)(CurrentTime - this->mLastTime) / 1000.f;
	this->mLastTime = CurrentTime;
	return DeltaTime;
}
