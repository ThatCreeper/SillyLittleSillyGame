#include "CGame.h"

CGame::CGame(CEngine *Engine)
{
	this->mEngine = Engine;
}

void CGame::Frame(float DeltaTime)
{
	this->mRenderer.ClearBackground(1, 0, 0);
	this->mRenderer.DrawRectangle(20, 20, this->mEngine->Width()/2 - 20, this->mEngine->Height()/2 - 20, 0, 1, 0);
	this->mRenderer.ConcludeDrawing();
}
