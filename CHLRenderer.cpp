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
	this->DisableTexture();
	gGLLib.VertexColor(R, G, B, 1);
	gGLLib.IntVertex(X, Y);
	gGLLib.IntVertex(X + W, Y);
	gGLLib.IntVertex(X + W, Y + H);
	gGLLib.IntVertex(X, Y + H);
}

void CHLRenderer::CopyTexture(CTexture &Texture, int X, int Y)
{
	// I'm almost certain that this isn't how you're supposed to do this.
	// (I think you're supposed to use glActiveTexture / glBind.
	//  I want to get this working first, though.)
	if (mCurrentTexture != &Texture) {
		mCurrentTexture = &Texture;
		Texture.Bind();
		gGLLib.EnableTexture();
	}
	this->SetRenderMode(ERenderMode::Quads);
	gGLLib.VertexColor(1, 1, 1, 1);
	gGLLib.TextureCoordinate(0, 0);
	gGLLib.IntVertex(X, Y);
	gGLLib.TextureCoordinate(1, 0);
	gGLLib.IntVertex(X + Texture.Width(), Y);
	gGLLib.TextureCoordinate(1, 1);
	gGLLib.IntVertex(X + Texture.Width(), Y + Texture.Height());
	gGLLib.TextureCoordinate(0, 1);
	gGLLib.IntVertex(X, Y + Texture.Height());
}

void CHLRenderer::ConcludeDrawing()
{
	Assert(this->mDrawing);
	gGLLib.EndDrawing();
	this->mDrawing = false;
	DisableTexture();
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

void CHLRenderer::DisableTexture()
{
	if (!this->mCurrentTexture) return;
	this->mCurrentTexture = nullptr;
	gGLLib.DisableTexture();
}

CShared<CTexture> CTexture::FromBMP(CStringView BMP)
{
	CShared<CTexture> tex(new CTexture);
	const char *data = BMP.Data();
	tex->mWidth = *reinterpret_cast<const int *>(data + 0x12);
	tex->mHeight = *reinterpret_cast<const int *>(data + 0x16);
	Assert(*reinterpret_cast<const short *>(data + 0x1C) == 32);
	gGLLib.EnableTexture();
	tex->Bind();
	gGLLib.UploadTexture(ETextureTarget::Texture2D, tex->mWidth, tex->mHeight, EInternalFormat::RGBA8, EFormat::RGBA, EPixelType::UnsignedByte, data + *reinterpret_cast<const int *>(data + 0x0A));
	gGLLib.DisableTexture();
	return tex;
}

CTexture::CTexture()
{
	mHandle = gGLLib.CreateTexture();
}

CTexture::~CTexture()
{
	gGLLib.DestroyTexture(mHandle);
}

void CTexture::Bind()
{
	gGLLib.BindTexture(ETextureTarget::Texture2D, mHandle);
}

int CTexture::Width() {
	return mWidth;
}

int CTexture::Height() {
	return mHeight;
}