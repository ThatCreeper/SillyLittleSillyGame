#include "CLevel.h"

#include "CStringSplitter.h"
#include "CGLLib.h"
#include "CFile.h"
#include "CConsole.h"
#include "CLevelReader.h"

CLevel::CLevel(CStringView Name)
{
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
				this->mActors[i] = MakeActor(View.Trimmed(), &Reader);
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
	gGLLib.SetViewport(380, 240);

	//gGLLib.SetClearColor(0, 0, 0, 1);
	//gGLLib.ClearBuffers(EClearBuffer::Color);

	for (int i = 0; i < this->ActorCount; i++)
		if (this->mActors[i])
			this->mActors[i]->Draw();
}
