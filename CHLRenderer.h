#pragma once
#include "CStringView.h"
#include "CShared.h"
#include "CGLLib.h"

class CTexture {
public:
	static CShared<CTexture> FromBMP(CStringView BMP);

	explicit CTexture();
	~CTexture();

	void Bind();

	int Width();
	int Height();

private:
	SGLTextureHandle mHandle;
	int mWidth = 0;
	int mHeight = 0;

	friend class CHLRenderer;
};

// High-level renderer
// (About Raylib high-level)
class CHLRenderer
{
public:
	void ClearBackground(float R, float G, float B);
	void DrawRectangle(int X, int Y, int W, int H, float R, float G, float B);
	void CopyTexture(CTexture &Texture, int X, int Y);
	void ConcludeDrawing();

private:
	enum class ERenderMode {
		Quads
	};

	void EnableRenderMode(ERenderMode Mode);
	void SetRenderMode(ERenderMode Mode);
	void DisableTexture();

	CTexture *mCurrentTexture = nullptr;
	bool mDrawing = false;
	ERenderMode mCurrentRenderMode = ERenderMode::Quads;
};

