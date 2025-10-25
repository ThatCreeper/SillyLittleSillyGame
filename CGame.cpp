#include "CGame.h"

CGame::CGame(CEngine *Engine)
	: mFile("demo_spr.bmp", EFileType::Read)
{
	this->mEngine = Engine;
	this->mTex = CTexture::FromBMP(mFile.ReadAll());
}

void CGame::Frame(float DeltaTime)
{
	this->mRenderer.ClearBackground(1, 0, 0);
	this->mRenderer.DrawRectangle(20, 20, this->mEngine->Width()/2 - 20, this->mEngine->Height()/2 - 20, 0, 1, 0);
	this->mRenderer.CopyTexture(*mTex, 0, 0);
	
	/*{
		const char *data = mFile.ReadAll().Data();
		int width = *reinterpret_cast<const int *>(data + 0x12);
		int height = *reinterpret_cast<const int *>(data + 0x16);
		Assert(*reinterpret_cast<const short *>(data + 0x1C) == 32);
		gGLLib.CopyPixelBuffer(0, 0, width, height, data + *reinterpret_cast<const int *>(data + 0x0A));
		Assert(!gGLLib.GetLastError());
	}*/
}
