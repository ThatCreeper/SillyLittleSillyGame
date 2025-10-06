#include "CEngine.h"

#include "CConsole.h"
#include "CGame.h"

static CEngine *gEngineSingleton;

long long WindowProcedure(HWindow Window, EMessageKind MessageKind, long long WParam, long long LParam) {
	switch (MessageKind) {
	case EMessageKind::Paint:
		SPaintStruct paint = gUserLib.BeginPainting(Window);
		gUserLib.EndPainting(Window, &paint);
		return 0;
	case EMessageKind::Destroyed:
		gUserLib.StopMessageQueue();
		return 0;
	case EMessageKind::EraseBackground:
		return 0;
	case EMessageKind::KeyDown:
		return 0;
	case EMessageKind::KeyUp:
		return 0;
	case EMessageKind::Size:
		gEngineSingleton->mWindowWidth = LoWord(LParam);
		gEngineSingleton->mWindowHeight = HiWord(LParam);
		return 0;
	}
	return gUserLib.DefaultWindowProcedure()(Window, MessageKind, WParam, LParam);
}

CEngine::CEngine()
{
	Assert(gEngineSingleton == nullptr);
	gEngineSingleton = this;

	gUserLib.RegisterClass("WinClass", WindowProcedure);
	this->mWindow = gUserLib.CreateWindow("WinClass", "Test Window", mWindowWidth, mWindowHeight);

	// These are leaked because I frankly don't want to deal with them properly
	this->mDeviceContext = gUserLib.GetWindowDeviceContext(this->mWindow);

	gGLLib.RequestSanePixelFormat(this->mDeviceContext);

	this->mGLContext = gGLLib.MakeGLContext(this->mDeviceContext);
	gGLLib.MakeContextCurrent(this->mDeviceContext, this->mGLContext);

	gGLLib.LoadExtensions();
	gGLLib.EnableVSync();

	gUserLib.ShowWindow(this->mWindow);

	this->mLastTime = GetTimeMilliseconds();

	this->mGame = new CGame(this);
}

CEngine::~CEngine()
{
	//delete this->mLevel;
	// Leak everything else; program is closing
}

void CEngine::Loop()
{
	SWindowMessage WindowMessage;
	while (true) {
		while (gUserLib.PeekQueuedMessage(&WindowMessage)) {
			if (gUserLib.PopQueuedMessage(&WindowMessage)) {
				gUserLib.TranslateVirtualKeyMessages(&WindowMessage);
				gUserLib.CallRelevantWindowProcedure(&WindowMessage);
			}
			else {
				return;
			}
		}
		Frame();
	}
}

void CEngine::Frame()
{
	float DeltaTime = this->GetDeltaTime();
	
	// TODO: Don't do this every frame lol
	gGLLib.SetViewport(mWindowWidth, mWindowHeight);
	gGLLib.SetMatrixMode(EMatrixMode::Projection);
	gGLLib.LoadIdentityMatrix();
	gGLLib.OrthoMatrix(0, mWindowWidth, mWindowHeight, 0, 0, 1);
	gGLLib.SetMatrixMode(EMatrixMode::ModelView);
	gGLLib.LoadIdentityMatrix();
	this->mGame->Frame(DeltaTime);

	gGLLib.Flush();
	gGLLib.SwapBuffers(this->mDeviceContext);
}

int CEngine::Width()
{
	return mWindowWidth;
}

int CEngine::Height()
{
	return mWindowHeight;
}

float CEngine::GetDeltaTime()
{
	unsigned long long CurrentTime = GetTimeMilliseconds();
	float DeltaTime = (float)(CurrentTime - this->mLastTime) / 1000.f;
	this->mLastTime = CurrentTime;
	return DeltaTime;
}
