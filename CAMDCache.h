#pragma once

// My graphics drivers don't keep their DLLs loaded,
// so I have to instead.
// This helper thing fixes the constant Load/FreeLibrary
// usage, but my drivers still end up flooding my debug
// console with "Thread Destroyed" whenever I resize
// my window.
class CAMDCache
{
public:
	CAMDCache();
};

