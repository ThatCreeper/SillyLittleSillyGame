#pragma once

#include "CStringView.h"
#include "AActor.h"

class CLevel
{
public:
	static constexpr int ActorCount = 256;

	CLevel(CStringView Name);
	~CLevel();

	void Draw();

protected:
	AActor *mActors[ActorCount] = { 0 };
};

