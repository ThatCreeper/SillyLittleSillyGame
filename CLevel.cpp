#include "CLevel.h"

#include "CStringSplitter.h"
#include "CGLLib.h"
#include "CFile.h"

CLevel::CLevel(CStringView Name)
{
	CString FilePath("Levels/");
	FilePath += Name;
	CFile File(FilePath.View(), EFileType::Read);
	CStringSplitter Splitter(File.ReadAll(), '\n');

	this->mR = Splitter.NextLineNoComment('#').ParseFloat();
	this->mG = Splitter.NextLineNoComment('#').ParseFloat();
	this->mB = Splitter.NextLineNoComment('#').ParseFloat();
}

void CLevel::Draw()
{
	gGLLib.SetClearColor(this->mR, this->mG, this->mB, 1);
	gGLLib.ClearBuffers(EClearBuffer::Color);
}
