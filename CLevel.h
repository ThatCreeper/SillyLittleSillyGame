#pragma once

#include "CStringView.h"
#include "AActor.h"

class CLevel
{
public:
	static constexpr int ActorCount = 256;

	CLevel(CEngine *Engine, CStringView Name);
	~CLevel();

	void Draw();

	void Remove(AActor *Actor);

protected:
	AActor *mActors[ActorCount] = { 0 };
	CEngine *mEngine;
};

