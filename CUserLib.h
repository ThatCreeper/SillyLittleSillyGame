#pragma once

#include "Core.h"

class CUserLib {
public:
	CUserLib();
	~CUserLib();

	static void Open();
	static void Close();


private:
	HLibrary mUserLib;
};

extern CUserLib gUserLib;
