#include "MultiChoiceDefSchedule.h"
#include "ContentField.h"

static const char* s_ppchNames[] = 
{
	"normal",
	"add",
	"delete",
	"replace"
};

CMultiChoiceDefSchedule::CMultiChoiceDefSchedule(CContentField& oForField) :
	CMultiChoiceDef(oForField)
{
}

CMultiChoiceDefSchedule::~CMultiChoiceDefSchedule()
{
}

size_t CMultiChoiceDefSchedule::getChoiceCount() const
{
	return (sizeof(s_ppchNames) / sizeof(char*));
}

const char* CMultiChoiceDefSchedule::getChoiceName(int iChoice) const
{
	if (iChoice < 1 || (size_t)iChoice > getChoiceCount())
	{
		return NULL;
	}

	return s_ppchNames[iChoice - 1];
}
