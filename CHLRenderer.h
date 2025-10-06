#pragma once

class CHLRenderer
{
public:
	void ClearBackground(float R, float G, float B);
	void DrawRectangle(int X, int Y, int W, int H, float R, float G, float B);
	void ConcludeDrawing();

private:
	enum class ERenderMode {
		Quads
	};

	void EnableRenderMode(ERenderMode Mode);
	void SetRenderMode(ERenderMode Mode);

	bool mDrawing = false;
	ERenderMode mCurrentRenderMode = ERenderMode::Quads;
};

