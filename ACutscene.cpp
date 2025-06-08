#include "ACutscene.h"

#include "CFile.h"
#include "CConsole.h"

DEF_ACTOR(ACutscene)

ACutscene::ACutscene(CEngine *Engine, CLevelReader *Reader)
	: AActor(Engine)
{
	CStringView Cutscene = Reader->Line();
	
	{
		CString FilePath("Cutscene/");
		FilePath += Cutscene;
		CFile File(FilePath, EFileType::Read);
		this->mDialogContents = File.ReadAll();
	}
	CLevelReader CutsceneReader(this->mDialogContents.View());

	while (true) {
		CStringView Line = CutsceneReader.Line();
		if (Line.Invalid())
			break;
		Line = Line.Trimmed();
		if (Line == "Dialog")
			AddDialog(&CutsceneReader);
		else
			Panic();
	}
}

void ACutscene::Draw()
{
	gConsole.Write("'", this->mActions[0].Text, "'\n");
}

void ACutscene::AddDialog(CLevelReader *Reader)
{
	if (this->mActionCount >= this->ActionCount)
		Panic();
	SCutsceneAction *Action = &this->mActions[this->mActionCount++];
	Action->Type = ECutsceneAction::Dialog;
	Action->Text = Reader->Line();
}
