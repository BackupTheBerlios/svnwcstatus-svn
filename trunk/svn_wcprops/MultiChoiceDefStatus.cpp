#include "MultiChoiceDefStatus.h"
#include "ContentField.h"

static const char* s_ppchNames[] = 
{
	"none",
	"unversioned",
	"normal",
	"added",
	"missing",
	"deleted",
	"replaced",
	"modified",
	"merged",
	"conflicted",
	"ignored",
	"obstructed",
	"external",
	"incomplete"
};

CMultiChoiceDefStatus::CMultiChoiceDefStatus(CContentField& oForField) :
	CMultiChoiceDef(oForField)
{
}

CMultiChoiceDefStatus::~CMultiChoiceDefStatus()
{
}

size_t CMultiChoiceDefStatus::getChoiceCount() const
{
	return (sizeof(s_ppchNames) / sizeof(char*));
}

const char* CMultiChoiceDefStatus::getChoiceName(int iChoice) const
{
	if (iChoice < 1 || (size_t)iChoice > getChoiceCount())
	{
		return NULL;
	}

	return s_ppchNames[iChoice - 1];
}
