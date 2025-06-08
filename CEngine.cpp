#include "CEngine.h"

#include "CConsole.h"

static CEngine *gEngineSingleton;

long long WindowProcedure(HWindow Window, EMessageKind MessageKind, long long WParam, long long LParam) {
	switch (MessageKind) {
	case EMessageKind::Paint:
		gEngineSingleton->Frame();
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
	case EMessageKind::Sizing:
		{
			SPaintRect *Rect = (SPaintRect *)LParam;
			int Width = Rect->Right - Rect->Left;
			int Multiple = Width / 284;
			if (Multiple < 1)
				Multiple = 1;
			Rect->Right = Rect->Left + Multiple * 284;
			Rect->Bottom = Rect->Top + Multiple * 160;
			return 1;
		}
	}
	return gUserLib.DefaultWindowProcedure()(Window, MessageKind, WParam, LParam);
}

CEngine::CEngine(CStringView LevelName)
{
	gEngineSingleton = this;

	gUserLib.RegisterClass("WinClass", WindowProcedure);
	this->mWindow = gUserLib.CreateWindow("WinClass", "Test Window", 284 * 2, 160 * 2);

	// These are leaked because I frankly don't want to deal with them properly
	this->mDeviceContext = gUserLib.GetWindowDeviceContext(this->mWindow);

	gGLLib.RequestSanePixelFormat(this->mDeviceContext);

	this->mGLContext = gGLLib.MakeGLContext(this->mDeviceContext);
	gGLLib.MakeContextCurrent(this->mDeviceContext, this->mGLContext);

	gGLLib.LoadExtensions();
	gGLLib.EnableVSync();

	gUserLib.ShowWindow(this->mWindow);

	this->mLastTime = GetTimeMilliseconds();

	this->mLevel = new CLevel(LevelName);
}

CEngine::~CEngine()
{
	delete this->mLevel;
	// Leak everything else; program is closing
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
	
	this->mLevel->Draw();

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
