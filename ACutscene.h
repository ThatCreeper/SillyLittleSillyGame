#pragma once

#include "AActor.h"
#include "CString.h"

enum class ECutsceneAction {
	Dialog
};

struct SCutsceneAction {
	ECutsceneAction Type = (ECutsceneAction) 0;
	union {
		int Nonsense = 0;
		CStringView Text;
	};
};

class ACutscene : public AActor {
public:
	static constexpr int ActionCount = 16;

	ACutscene(CEngine *Engine, CLevelReader *Reader);

	void Draw() override;

protected:
	void AddDialog(CLevelReader *Reader);

	int mActionCount = 0;
	SCutsceneAction mActions[ActionCount] = {};
	CString mDialogContents;
};

