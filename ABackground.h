#pragma once

#include "AActor.h"

class ABackground : public AActor
{
public:
	ABackground(CEngine *Engine, CLevelReader *Reader);
	~ABackground() override;

	void Draw() override;
	
protected:
	float R;
	float G;
	float B;
};
