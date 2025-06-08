#include "CLevel.h"

#include "CStringSplitter.h"
#include "CGLLib.h"
#include "CFile.h"
#include "CConsole.h"
#include "CLevelReader.h"

CLevel::CLevel(CEngine *Engine, CStringView Name)
{
	this->mEngine = Engine;

	gConsole.Write("CLevel: Loading map ", Name, "\n");

	CString FilePath("Levels/");
	FilePath += Name;
	CFile File(FilePath.View(), EFileType::Read);
	CLevelReader Reader(File.ReadAll());

	while (true) {
		CStringView View = Reader.Line();
		bool Added = false;
		if (View.Invalid())
			break;
		for (int i = 0; i < this->ActorCount; i++) {
			if (!this->mActors[i]) {
				this->mActors[i] = MakeActor(View.Trimmed(), this->mEngine, &Reader);
				Added = true;
				break;
			}
		}
		if (!Added)
			Panic();
	}
}

CLevel::~CLevel()
{
	for (int i = 0; i < this->ActorCount; i++) {
		delete this->mActors[i];
	}
}

void CLevel::Draw()
{
	gGLLib.SetViewport(284, 160);

	//gGLLib.SetClearColor(0, 0, 0, 1);
	//gGLLib.ClearBuffers(EClearBuffer::Color);

	for (int i = 0; i < this->ActorCount; i++)
		if (this->mActors[i])
			this->mActors[i]->Draw();
}

void CLevel::Remove(AActor *Actor)
{
	if (!Actor)
		return;
	for (int i = 0; i < this->ActorCount; i++) {
		if (this->mActors[i] == Actor) {
			delete this->mActors[i];
			this->mActors[i] = nullptr;
		}
	}
}
