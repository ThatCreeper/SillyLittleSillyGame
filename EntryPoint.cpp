#include "Core.h"
#include "CConsole.h"
#include "CUserLib.h"
#include "CString.h"
#include "CGLLib.h"

void Panic() {
	gConsole.Write("Panic()! Did you set a breakpoint? Last Win Error: ");
	gConsole.WriteInteger(GetWinAPIError());

	// Set Break-point Here!
	gConsole.WaitForLine();
	Exit(1);
}

int Frame = 0;
unsigned long long lastTime = -1;

long long WindowProcedure(HWindow Window, EMessageKind MessageKind, long long WParam, long long LParam) {
	switch (MessageKind) {
	case EMessageKind::Paint:
		{
			unsigned long long curTime = GetTimeMilliseconds();
			if (Frame++ % 60 == 0)
				gConsole.WriteInteger(Frame / 60);

			float r = (float)(curTime - lastTime) / 5000.f;
			gGLLib.SetClearColor(r, 0, 1, 1);
			gGLLib.ClearBuffers(EClearBuffer::Color);
			gGLLib.Flush();
			SPaintStruct paint = gUserLib.BeginPainting(Window);
			gUserLib.EndPainting(Window, &paint);

			gUserLib.RequestAnimationFrame(Window);
			return 0;
		}
	case EMessageKind::Destroyed:
		gUserLib.StopMessageQueue();
		return 0;
	}
	return gUserLib.DefaultWindowProcedure()(Window, MessageKind, WParam, LParam);
}

int main() {
	CUserLib::Open();
	CGLLib::Open();

	gUserLib.RegisterClass("WinClass", WindowProcedure);
	HWindow Window = gUserLib.CreateWindow("WinClass", "Test Window", 500, 500);

	// These are leaked because I frankly don't want to deal with them properly
	HDeviceContext DeviceContext = gUserLib.GetWindowDeviceContext(Window);

	gGLLib.RequestSanePixelFormat(DeviceContext);

	HGLContext GLContext = gGLLib.MakeGLContext(DeviceContext);
	gGLLib.MakeContextCurrent(DeviceContext, GLContext);
	
	gGLLib.LoadExtensions();
	gGLLib.EnableVSync();

	gUserLib.ShowWindow(Window);

	lastTime = GetTimeMilliseconds();

	SWindowMessage WindowMessage;
	while (gUserLib.PopQueuedMessage(&WindowMessage)) {
		gUserLib.TranslateVirtualKeyMessages(&WindowMessage);
		gUserLib.CallRelevantWindowProcedure(&WindowMessage);
	}

	CGLLib::Close();
	CUserLib::Close();
	return 0;
}