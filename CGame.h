#pragma once

#include "CEngine.h"
#include "CHLRenderer.h"
#include "CFile.h"

class CGame
{
public:
	CGame(CEngine *Engine);

	void Frame(float DeltaTime);

private:
	CEngine *mEngine;
	CHLRenderer mRenderer;

	CShared<CTexture> mTex;
	CFile mFile;
};

