#include "CoreWin.h"
#include "CAllocator.h"
#include "CConsole.h"

int main();

extern "C" int _fltused = 0;

unsigned long long gPerfCounterFrequency;

static void SetupPerformanceCounter() {
	QueryPerformanceFrequency(&gPerfCounterFrequency);
	gPerfCounterFrequency /= 1000;
}

/* SOMEWHAT DOCUMENTED CRT RITUAL STOLEN FROM THE CRT */
// I only actually care about the C(++) initializers here.
typedef void(__cdecl *_PVFV)(void);
typedef int(__cdecl *_PIFV)(void);
#pragma section(".CRT$XIA", long, read)
#pragma section(".CRT$XIZ", long, read)
#pragma section(".CRT$XCA", long, read)
#pragma section(".CRT$XCZ", long, read)
#pragma section(".CRT$XPA", long, read)
#pragma section(".CRT$XPZ", long, read)
#pragma section(".CRT$XTA", long, read)
#pragma section(".CRT$XTZ", long, read)
extern "C" __declspec(allocate(".CRT$XIA")) _PIFV __xi_a[] = { nullptr }; // C initializers (first)
extern "C" __declspec(allocate(".CRT$XIZ")) _PIFV __xi_z[] = { nullptr }; // C initializers (last)
extern "C" __declspec(allocate(".CRT$XCA")) _PVFV __xc_a[] = { nullptr }; // C++ initializers (first)
extern "C" __declspec(allocate(".CRT$XCZ")) _PVFV __xc_z[] = { nullptr }; // C++ initializers (last)
extern "C" __declspec(allocate(".CRT$XPA")) _PVFV __xp_a[] = { nullptr }; // C pre-terminators (first)
extern "C" __declspec(allocate(".CRT$XPZ")) _PVFV __xp_z[] = { nullptr }; // C pre-terminators (last)
extern "C" __declspec(allocate(".CRT$XTA")) _PVFV __xt_a[] = { nullptr }; // C terminators (first)
extern "C" __declspec(allocate(".CRT$XTZ")) _PVFV __xt_z[] = { nullptr }; // C terminators (last)
#pragma comment(linker, "/merge:.CRT=.rdata")

static void SetupCppInitializers() {
	int deniedConstructors = 0;
	for (_PVFV *i = __xc_a + 1; i < __xc_z; i++) {
		// TODO: This is a magic number I found
		// by looking at things. This probably
		// breaks under certain circumstances,
		// and it's almost certainly MSVC
		// exclusive. Eventually, I should try
		// to figure out how to replace this
		// with something better.
#define IS_CONSTRUCTOR_OF(Instance) (long long)&Instance - (long long)i == 8024
#define DENY_CONSTRUCTOR_OF(Instance) if (IS_CONSTRUCTOR_OF(Instance)) {deniedConstructors++;continue;}
		
		DENY_CONSTRUCTOR_OF(gAllocator);
		DENY_CONSTRUCTOR_OF(gConsole);
		
		(*i)();
	}
	Assert(deniedConstructors == 2);
}

template<class PointerType>
static void AssertNoneBetween(PointerType a, PointerType b) {
	Assert(a + 1 == b);
}

// The parameter to this function is unused in the example provided by the Visual C Runtime.
extern "C" int mainCRTStartup(void *) {
	SetLastError(0);

	new(&gAllocator)CAllocator;
	new(&gConsole)CConsole;

	SetupPerformanceCounter();

	AssertNoneBetween(__xi_a, __xi_z);
	AssertNoneBetween(__xp_a, __xp_z);
	AssertNoneBetween(__xt_a, __xt_z);
	SetupCppInitializers();

	int Ret = main();

	CallExitHandlers();
	
	ExitProcess(Ret);
	return Ret;
}