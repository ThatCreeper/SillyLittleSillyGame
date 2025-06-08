#pragma once

#include "AActor.h"

class ABackground : public AActor
{
public:
	ABackground(CLevelReader *Reader);
	~ABackground() override;

	void Draw() override;
	
protected:
	float R;
	float G;
	float B;
};
