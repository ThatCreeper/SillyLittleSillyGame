#pragma once

#include "CLevelReader.h"

class CEngine;

class AActor
{
public:
	AActor(CEngine *Engine);
	virtual ~AActor();

	virtual void Draw();

protected:
	void Remove();

	CEngine *mEngine;
};

#define DEF_ACTOR(Actor) AActor *MakeActor##Actor(CEngine *Engine, CLevelReader *Reader) {return new Actor(Engine, Reader);}

AActor *MakeActor(CStringView ActorType, CEngine *Engine, CLevelReader *Reader);