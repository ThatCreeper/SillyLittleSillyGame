#include "CHLRenderer.h"

#include "CGLLib.h"

void CHLRenderer::ClearBackground(float R, float G, float B)
{
	gGLLib.SetClearColor(R, G, B, 1);
	gGLLib.ClearBuffers(EClearBuffer::Color);
}

void CHLRenderer::DrawRectangle(int X, int Y, int W, int H, float R, float G, float B)
{
	gGLLib.BeginQuads();
	gGLLib.VertexColor(R, G, B, 1);
	gGLLib.IntVertex(X, Y);
	gGLLib.IntVertex(X + W, Y);
	gGLLib.IntVertex(X + W, Y + H);
	gGLLib.IntVertex(X, Y + H);
	gGLLib.EndDrawing();
}

void CHLRenderer::CopyTexture(CTexture &Texture, int X, int Y)
{
	// I'm almost certain that this isn't how you're supposed to do this.
	// (I think you're supposed to use glActiveTexture / glBind.
	//  I want to get this working first, though.)
	/*if (mCurrentTexture != &Texture) {
		mCurrentTexture = &Texture;
		gGLLib.EnableTexture();
		Texture.Bind();
	}*/
	gGLLib.EnableTexture();
	Texture.Bind();
	gGLLib.BeginQuads();
	gGLLib.VertexColor(0, 1, 1, 1);
	gGLLib.TextureCoordinate(0, 0);
	gGLLib.IntVertex(X, Y);
	gGLLib.TextureCoordinate(10, 0);
	gGLLib.IntVertex(X + Texture.Width() * 10, Y);
	gGLLib.TextureCoordinate(10, 1);
	gGLLib.IntVertex(X + Texture.Width() * 10, Y + Texture.Height() * 10);
	gGLLib.TextureCoordinate(0, 1);
	gGLLib.IntVertex(X, Y + Texture.Height() * 10);
	gGLLib.EndDrawing();
	gGLLib.DisableTexture();
}

void CHLRenderer::ConcludeDrawing()
{
	Panic();
	//Assert(this->mDrawing);
	//gGLLib.EndDrawing();
	//this->mDrawing = false;
	//DisableTexture();
}

void CHLRenderer::EnableRenderMode(ERenderMode Mode)
{
	Panic();

	//switch (Mode) {
	//case ERenderMode::Quads:
	//	gGLLib.BeginQuads();
	//	break;
	//default:
	//	Panic();
	//	break;
	//}
}

void CHLRenderer::SetRenderMode(ERenderMode Mode)
{
	Panic();
	//if (this->mDrawing && this->mCurrentRenderMode == Mode)
	//	return;
	//this->EnableRenderMode(Mode);
	//this->mDrawing = true;
	//this->mCurrentRenderMode = Mode;
}

void CHLRenderer::DisableTexture()
{
	Panic();
	//if (!this->mCurrentTexture) return;
	//this->mCurrentTexture = nullptr;
	//gGLLib.DisableTexture();
}

CShared<CTexture> CTexture::FromBMP(CStringView BMP)
{
	/*CShared<CTexture> tex(new CTexture);
	const char *data = BMP.Data();
	tex->mWidth = *reinterpret_cast<const int *>(data + 0x12);
	tex->mHeight = *reinterpret_cast<const int *>(data + 0x16);
	Assert(*reinterpret_cast<const short *>(data + 0x1C) == 32);
	gGLLib.EnableTexture();
	tex->Bind();
	gGLLib.UploadTexture(ETextureTarget::Texture2D, tex->mWidth, tex->mHeight, EInternalFormat::RGBA8, EFormat::RGBA, EPixelType::UnsignedByte, data + *reinterpret_cast<const int *>(data + 0x0A));
	gGLLib.DisableTexture();*/
	CShared<CTexture> tex(new CTexture);
	Assert(!gGLLib.GetLastError());
	char data[] = {
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255,
		255, 255, 0, 255
	};
	tex->mWidth = 2;
	tex->mHeight = 2;
	tex->Bind();
	Assert(!gGLLib.GetLastError());
	gGLLib.UploadTexture(ETextureTarget::Texture2D, tex->mWidth, tex->mHeight, EInternalFormat::RGBA8, EFormat::RGBA, EPixelType::UnsignedByte, data);
	Assert(!gGLLib.GetLastError());
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