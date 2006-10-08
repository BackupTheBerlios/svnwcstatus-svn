#include "MultiChoiceDef.h"

CMultiChoiceDef::CMultiChoiceDef(CContentField& oForField) :
	m_oForField(oForField)
{
}

CMultiChoiceDef::~CMultiChoiceDef()
{
}

const CContentField& CMultiChoiceDef::getField() const
{
	return m_oForField;
}

int CMultiChoiceDef::normalizeChoice(int iChoice) const
{
	if (iChoice > 0 && (size_t)iChoice <= getChoiceCount())
	{
		return iChoice;
	}
	
	if (iChoice == eMultiChoiceEmpty)
	{
		return eMultiChoiceEmpty;
	}

	if (iChoice == eMultiChoiceError)
	{
		return eMultiChoiceError;
	}

	return eMultiChoiceInvalidIndex;
}
