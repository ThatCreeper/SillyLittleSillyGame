#include "CLevel.h"

#include "CStringSplitter.h"
#include "CGLLib.h"
#include "CFile.h"

namespace {
	class CLevelReader {
	public:
		CLevelReader(CStringView Data)
			: mSplitter(Data, '\n')
		{
		}

		CStringView Line() {
			return this->mSplitter.NextLineNoComment('#');
		}

		int Int() {
			return this->Line().ParseInteger();
		}

		float Float() {
			return this->Line().ParseFloat();
		}

	protected:
		CStringSplitter mSplitter;
	};
}

CLevel::CLevel(CStringView Name)
{
	CString FilePath("Levels/");
	FilePath += Name;
	CFile File(FilePath.View(), EFileType::Read);
	CLevelReader Reader(File.ReadAll());

	this->mR = Reader.Float();
	this->mG = Reader.Float();
	this->mB = Reader.Float();
}

void CLevel::Draw()
{
	gGLLib.SetClearColor(this->mR, this->mG, this->mB, 1);
	gGLLib.ClearBuffers(EClearBuffer::Color);
}
