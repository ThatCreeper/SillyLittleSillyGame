#include "AActor.h"

#include "Core.h"
#include "CEngine.h"

AActor::AActor(CEngine *Engine)
{
	this->mEngine = Engine;
}

AActor::~AActor()
{
}

void AActor::Draw() {

}

void AActor::Remove()
{
	this->mEngine->Level()->Remove(this);
}

#define ACTORS_X \
	X(ABackground) \
	X(ACutscene)

#define X(Actor) AActor *MakeActor##Actor(CEngine *Engine, CLevelReader *Reader);
ACTORS_X
#undef X

#define X(Actor) #Actor,
static const char *gActorNames[] = {
	ACTORS_X
};
#undef X

#define X(Actor) MakeActor##Actor,
static AActor * (*gActorFunctions[])(CEngine *, CLevelReader *) = {
	ACTORS_X
};
#undef X

AActor *MakeActor(CStringView ActorType, CEngine *Engine, CLevelReader *Reader)
{
	constexpr int ActorLength = sizeof(gActorFunctions) / sizeof(*gActorFunctions);
	for (int i = 0; i < ActorLength; i++) {
		CStringView Name(gActorNames[i]);
		if (Name == ActorType) {
				return gActorFunctions[i](Engine, Reader);
		}
	}
	Panic();
	return nullptr;
}
