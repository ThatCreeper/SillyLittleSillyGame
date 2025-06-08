#include "CLevelReader.h"

CLevelReader::CLevelReader(CStringView Data)
	: mSplitter(Data, '\n')
{
}

CStringView CLevelReader::Line() {
	return this->mSplitter.NextLineNoComment('#');
}

int CLevelReader::Int() {
	return this->Line().ParseInteger();
}

float CLevelReader::Float() {
	return this->Line().ParseFloat();
}
