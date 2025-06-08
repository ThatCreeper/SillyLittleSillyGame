#pragma once

#include "CLevelReader.h"

class AActor
{
public:
	AActor();
	virtual ~AActor();

	virtual void Draw();

protected:
};

#define DEF_ACTOR(Actor) AActor *MakeActor##Actor(CLevelReader *Reader) {return new Actor(Reader);}

AActor *MakeActor(CStringView ActorType, CLevelReader *Reader);