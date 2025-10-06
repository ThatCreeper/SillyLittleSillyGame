#include "CHLRenderer.h"

#include "CGLLib.h"

void CHLRenderer::ClearBackground(float R, float G, float B)
{
	gGLLib.SetClearColor(R, G, B, 1);
	gGLLib.ClearBuffers(EClearBuffer::Color);
}

void CHLRenderer::DrawRectangle(int X, int Y, int W, int H, float R, float G, float B)
{
	this->SetRenderMode(ERenderMode::Quads);
	gGLLib.VertexColor(R, G, B, 1);
	gGLLib.IntVertex(X, Y);
	gGLLib.IntVertex(X + W, Y);
	gGLLib.IntVertex(X + W, Y + H);
	gGLLib.IntVertex(X, Y + H);
}

void CHLRenderer::ConcludeDrawing()
{
	Assert(this->mDrawing);
	gGLLib.EndDrawing();
	this->mDrawing = false;
}

void CHLRenderer::EnableRenderMode(ERenderMode Mode)
{
	switch (Mode) {
	case ERenderMode::Quads:
		gGLLib.BeginQuads();
		break;
	default:
		Panic();
		break;
	}
}

void CHLRenderer::SetRenderMode(ERenderMode Mode)
{
	if (this->mDrawing && this->mCurrentRenderMode == Mode)
		return;
	this->EnableRenderMode(Mode);
	this->mDrawing = true;
	this->mCurrentRenderMode = Mode;
}
