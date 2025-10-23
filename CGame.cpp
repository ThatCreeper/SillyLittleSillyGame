#include "CGame.h"
#include "CFile.h"

CGame::CGame(CEngine *Engine)
{
	this->mEngine = Engine;
	CFile file("demo_spr.bmp", EFileType::Read);
	this->mTex = CTexture::FromBMP(file.ReadAll());
}

void CGame::Frame(float DeltaTime)
{
	this->mRenderer.ClearBackground(1, 0, 0);
	this->mRenderer.DrawRectangle(20, 20, this->mEngine->Width()/2 - 20, this->mEngine->Height()/2 - 20, 0, 1, 0);
	this->mRenderer.CopyTexture(*mTex, 0, 0);
	this->mRenderer.ConcludeDrawing();
}
