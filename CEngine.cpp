#include "CEngine.h"

#include "CConsole.h"
#include "CGame.h"
#include "Math.h"

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
		// This says it's only called after the size has finished changing.
		// This is not true.
		// Ugh.
		gEngineSingleton->mWindowRealWidth = LoWord(LParam);
		gEngineSingleton->mWindowRealHeight = HiWord(LParam);
		// Uncomment for real window size correction
		// Check blame for technical reason
		//gEngineSingleton->UpdateDPI();
		gEngineSingleton->UpdateProjection();
		return 0;
	case EMessageKind::DPIChanged:
		//gEngineSingleton->UpdateDPI();
		gEngineSingleton->UpdateProjection();
		return 0;
	}
	return gUserLib.DefaultWindowProcedure()(Window, MessageKind, WParam, LParam);
}

void OpenGLCallback(int Source, int Type, unsigned int Id, int Severity, int Length, const char *Message, const void *User) {
	gConsole.Write(Message);
	gConsole.Write("\n");
	return;
}

CEngine::CEngine()
{
	Assert(gEngineSingleton == nullptr);
	gEngineSingleton = this;

	gUserLib.MarkProcessDPIAware();

	gUserLib.RegisterClass("WinClass", WindowProcedure);
	this->mWindow = gUserLib.CreateWindow("WinClass", "Test Window", mWindowWidth, mWindowHeight);

	this->UpdateDPI();

	// These are leaked because I frankly don't want to deal with them properly
	this->mDeviceContext = gUserLib.GetWindowDeviceContext(this->mWindow);

	gGLLib.RequestSanePixelFormat(this->mDeviceContext);

	this->mGLContext = gGLLib.MakeGLContext(this->mDeviceContext);
	gGLLib.MakeContextCurrent(this->mDeviceContext, this->mGLContext);

	gGLLib.LoadExtensions();
	gGLLib.SetDebugCallback(OpenGLCallback);
	gGLLib.EnableVSync();
	this->UpdateProjection();

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
	
	gGLLib.SetMatrixMode(EMatrixMode::ModelView);
	gGLLib.LoadIdentityMatrix();
	this->mGame->Frame(DeltaTime);

	gGLLib.Flush();
	gGLLib.SwapBuffers(this->mDeviceContext);
}

int CEngine::Width()
{
	return this->mWindowWidth;
}

int CEngine::Height()
{
	return this->mWindowHeight;
}

int CEngine::ScalingFactor()
{
	return this->mScalingFactor;
}

int CEngine::RealWidth()
{
	return this->mWindowRealWidth;
}

int CEngine::RealHeight()
{
	return this->mWindowRealHeight;
}

float CEngine::GetDeltaTime()
{
	unsigned long long CurrentTime = GetTimeMilliseconds();
	float DeltaTime = (float)(CurrentTime - this->mLastTime) / 1000.f;
	this->mLastTime = CurrentTime;
	return DeltaTime;
}

// WindowRealWidth and -Height must be set before calling.
void CEngine::UpdateDPI()
{
	this->mScalingFactor = Math::Floor(gUserLib.GetWindowScalingFactor(this->mWindow));
	// I don't actually think the scaling factor can be less than one.
	if (this->mScalingFactor < 2) this->mScalingFactor = 2;

	int widthWrongness = this->mWindowRealWidth % this->mScalingFactor;
	int heightWrongness = this->mWindowRealHeight % this->mScalingFactor;
	if (widthWrongness != 0 || heightWrongness != 0) {
		
		this->mWindowRealWidth += this->mScalingFactor - widthWrongness;
		this->mWindowRealHeight += this->mScalingFactor - heightWrongness;
		gUserLib.SetWindowSize(this->mWindow, this->mWindowRealWidth, this->mWindowRealHeight);
		return; // SetWindowSize acts as a deferred recursive call.
	}

	this->mWindowWidth = this->mWindowRealWidth / this->mScalingFactor;
	this->mWindowHeight = this->mWindowRealHeight / this->mScalingFactor;
}

void CEngine::UpdateProjection()
{
	gGLLib.SetViewport(mWindowRealWidth, mWindowRealHeight);
	gGLLib.SetMatrixMode(EMatrixMode::Projection);
	gGLLib.LoadIdentityMatrix();
	gGLLib.OrthoMatrix(0, mWindowWidth, mWindowHeight, 0, 0, 1);
	gGLLib.SetMatrixMode(EMatrixMode::Texture);
	gGLLib.LoadIdentityMatrix();
}
