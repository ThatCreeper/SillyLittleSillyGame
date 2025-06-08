#include "ABackground.h"

#include "CGLLib.h"

DEF_ACTOR(ABackground)

ABackground::ABackground(CEngine *Engine, CLevelReader *Reader)
	: AActor(Engine)
{
	this->R = Reader->Float();
	this->G = Reader->Float();
	this->B = Reader->Float();
}

ABackground::~ABackground()
{
}

void ABackground::Draw()
{
	gGLLib.SetClearColor(R, G, B, 1);
	gGLLib.ClearBuffers(EClearBuffer::Color);
}