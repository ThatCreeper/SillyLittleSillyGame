#include "CUserLib.h"

#include "CAllocator.h"
#include "CoreWin.h"

CUserLib gUserLib;

struct SWindowClass {
	unsigned int Style;
	FWindowProcedure WindowProcedure;
	int WindowClassExtraBytes;
	int WindowInstanceExtraBytes;
	HInstance ProcedureInstance;
	void *Icon;
	void *Cursor;
	void *BackgroundBrush;
	const char *MenuName;
	const char *ClassName;
};

CUserLib::CUserLib() {
	this->mUserLib = LoadLibraryA("user32.dll");
	this->mInstance = GetModuleHandleA(nullptr);

	// I'm sorry.
#define LOAD_USER(Name) *((void **)(&this->m##Name)) = (void *)GetProcAddress(this->mUserLib, #Name); Assert(this->m##Name)
	
	LOAD_USER(RegisterClassA);
	LOAD_USER(DefWindowProcA);
	LOAD_USER(CreateWindowExA);
	LOAD_USER(ShowWindow);
	LOAD_USER(GetMessageA);
	LOAD_USER(PeekMessageA);
	LOAD_USER(TranslateMessage);
	LOAD_USER(DispatchMessageA);
	LOAD_USER(PostQuitMessage);
	LOAD_USER(GetDC);
	LOAD_USER(BeginPaint);
	LOAD_USER(EndPaint);
	LOAD_USER(InvalidateRect);
	LOAD_USER(SetWindowPos);
	LOAD_USER(LoadCursorA);
	LOAD_USER(SetCursor);
	LOAD_USER(SetProcessDpiAwarenessContext);
	LOAD_USER(GetDpiForWindow);
	LOAD_USER(AdjustWindowRectExForDpi);

#undef LOAD_USER
}

CUserLib::~CUserLib() {
	FreeLibrary(this->mUserLib);
}

HInstance CUserLib::GetInstance() {
	return this->mInstance;
}

void CUserLib::RegisterClass(const char *ClassName, FWindowProcedure WindowProcedure) {
	SWindowClass WindowClass;
	WindowClass.Style = 0;
	WindowClass.WindowProcedure = WindowProcedure;
	WindowClass.WindowClassExtraBytes = 0;
	WindowClass.WindowInstanceExtraBytes = 0;
	WindowClass.ProcedureInstance = this->mInstance;
	WindowClass.Icon = nullptr;
	WindowClass.Cursor = this->LoadCursor(32512 /* IDC_ARROW */);
	WindowClass.BackgroundBrush = nullptr;
	WindowClass.MenuName = nullptr;
	WindowClass.ClassName = ClassName;

	this->mRegisterClassA(&WindowClass);
}

HWindow CUserLib::CreateWindow(const char *ClassName, const char *WindowName, int Width, int Height) {
	int Style = 0x00000000L  /* Overlapped */
	          | 0x00C00000L  /* Caption (Title Bar) */
	          | 0x00080000L  /* SysMenu (Title Bar Displays Menu) */
	          | 0x00040000L  /* Thick Frame (Resizable) */
	          | 0x00020000L  /* Minimize Box */
	          | 0x00010000L; /* Maximize Box */

	int DefaultPosition = ((int)0x80000000);

	return this->mCreateWindowExA(0, ClassName, WindowName, Style, DefaultPosition, DefaultPosition, Width, Height, nullptr, nullptr, this->mInstance, nullptr);
}

void CUserLib::ShowWindow(HWindow Window) {
	this->mShowWindow(Window, 1 /* Show Normal */);
}

bool CUserLib::PopQueuedWindowMessage(SWindowMessage *OutMessage, HWindow Window)
{
	return this->mGetMessageA(OutMessage, Window, 0 /* No Filter */, 0 /* No Filter */);
}

bool CUserLib::PopQueuedMessage(SWindowMessage *OutMessage)
{
	return this->PopQueuedWindowMessage(OutMessage, nullptr);
}

bool CUserLib::PeekQueuedWindowMessage(SWindowMessage *OutMessage, HWindow Window)
{
	return this->mPeekMessageA(OutMessage, Window, 0, 0, 0 /* PM_NOREMOVE */);
}

bool CUserLib::PeekQueuedMessage(SWindowMessage *OutMessage)
{
	return this->PeekQueuedWindowMessage(OutMessage, nullptr);
}

void CUserLib::TranslateVirtualKeyMessages(SWindowMessage *Message)
{
	this->mTranslateMessage(Message);
}

long long CUserLib::CallRelevantWindowProcedure(SWindowMessage *Message)
{
	return this->mDispatchMessageA(Message);
}

void CUserLib::StopMessageQueue()
{
	this->mPostQuitMessage(0 /* Exit Code */);
}

void CUserLib::SetWindowSize(HWindow Window, int Width, int Height)
{
	int Flags = 0x0010 /* No Activate */
	          | 0x0002 /* No Move */
	          | 0x0200 /* No Owner Z Order */;
	int Style = 0x00000000L  /* Overlapped */
		      | 0x00C00000L  /* Caption (Title Bar) */
		      | 0x00080000L  /* SysMenu (Title Bar Displays Menu) */
		      | 0x00040000L  /* Thick Frame (Resizable) */
		      | 0x00020000L  /* Minimize Box */
		      | 0x00010000L; /* Maximize Box */

	SPaintRect rect;
	rect.Top = rect.Left = 0;
	rect.Right = Width;
	rect.Bottom = Height;

	this->mAdjustWindowRectExForDpi(&rect, Style, false, 0, this->mGetDpiForWindow(Window));

	this->mSetWindowPos(Window, nullptr, 0, 0, rect.Right - rect.Left, rect.Bottom - rect.Top, Flags);
}

FWindowProcedure CUserLib::DefaultWindowProcedure()
{
	return this->mDefWindowProcA;
}

HDeviceContext CUserLib::GetWindowDeviceContext(HWindow Window)
{
	return this->mGetDC(Window);
}

SPaintStruct CUserLib::BeginPainting(HWindow Window)
{
	SPaintStruct PaintStruct;
	HDeviceContext Context = this->mBeginPaint(Window, &PaintStruct);
	Assert(Context == PaintStruct.DeviceContext);
	return PaintStruct;
}

void CUserLib::EndPainting(HWindow Window, SPaintStruct *PaintStruct)
{
	this->mEndPaint(Window, PaintStruct);
}

void CUserLib::RequestAnimationFrame(HWindow Window)
{
	this->mInvalidateRect(Window, nullptr, true /* Redraw Background */);
}

HCursor CUserLib::LoadCursor(int Cursor)
{
	return this->mLoadCursorA(nullptr, ((const char *)((unsigned long long)((unsigned short)(Cursor)))));
}

void CUserLib::MarkProcessDPIAware()
{
	this->mSetProcessDpiAwarenessContext(-4 /* Per-monitor DPI awareness version 2 */);
}

float CUserLib::GetWindowScalingFactor(HWindow Window)
{
	return this->mGetDpiForWindow(Window) / 96.0f;
}

int LoWord(long long Value)
{
	return Value & 0xFFFF;
}

int HiWord(long long Value)
{
	return (Value >> 16) & 0xFFFF;
}
