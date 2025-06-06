#pragma once

#include "CStringView.h"

class CLevel
{
public:
	CLevel(CStringView Name);

	void Draw();

protected:
	float mR;
	float mG;
	float mB;
};

