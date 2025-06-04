#include "CUserLib.h"

#include "CAllocator.h"
#include "CoreWin.h"

CUserLib gUserLib;

struct SWindowClass {
	unsigned int Style;
	long long (*WindowProcedure)(HWindow, unsigned int, unsigned long long, long long);
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
#define LOAD_USER(Name) *((int **)(&this->m##Name)) = (int *)GetProcAddress(this->mUserLib, #Name)
	
	LOAD_USER(RegisterClassA);
	LOAD_USER(DefWindowProcA);
	LOAD_USER(CreateWindowExA);
	LOAD_USER(ShowWindow);

#undef LOAD_USER
}

CUserLib::~CUserLib() {
	FreeLibrary(this->mUserLib);
}

void CUserLib::Open() {
	new(&gUserLib)CUserLib;
}

void CUserLib::Close() {
	gUserLib.~CUserLib();
}

HInstance CUserLib::GetInstance() {
	return this->mInstance;
}

void CUserLib::RegisterClass(const char *ClassName) {
	SWindowClass WindowClass;
	WindowClass.Style = 0;
	WindowClass.WindowProcedure = this->mDefWindowProcA;
	WindowClass.WindowClassExtraBytes = 0;
	WindowClass.WindowInstanceExtraBytes = 0;
	WindowClass.ProcedureInstance = this->mInstance;
	WindowClass.Icon = nullptr;
	WindowClass.Cursor = nullptr;
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
