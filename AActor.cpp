#include "AActor.h"

#include "Core.h"

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::Draw() {

}

#define ACTORS_X \
	X(ABackground)

#define X(Actor) AActor *MakeActor##Actor(CLevelReader *Reader);
ACTORS_X
#undef X

#define X(Actor) #Actor
static const char *gActorNames[] = {
	ACTORS_X
};
#undef X

#define X(Actor) MakeActor##Actor
static AActor * (*gActorFunctions[])(CLevelReader *) = {
	ACTORS_X
};
#undef X

AActor *MakeActor(CStringView ActorType, CLevelReader *Reader)
{
	constexpr int ActorLength = sizeof(gActorFunctions) / sizeof(*gActorFunctions);
	for (int i = 0; i < ActorLength; i++) {
		CStringView Name(gActorNames[i]);
		if (Name == ActorType) {
				return gActorFunctions[i](Reader);
		}
	}
	Panic();
	return nullptr;
}
