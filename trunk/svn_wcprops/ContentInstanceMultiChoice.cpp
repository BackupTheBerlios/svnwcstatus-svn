#include "ContentInstanceMultiChoice.h"
#include "MultiChoiceDef.h"
#include "ContentField.h"

CContentInstanceMultiChoice::CContentInstanceMultiChoice(const CMultiChoiceDef& oDef, const char* pchPath, int iChoice) :
	CContentInstance(oDef.getField(), pchPath),
	m_oDef(oDef),
	m_iChoiceItem(oDef.normalizeChoice(iChoice))
{
}

CContentInstanceMultiChoice::~CContentInstanceMultiChoice()
{
}

int CContentInstanceMultiChoice::copyValueTo(void** ppBuf, int iMaxBuf) const
{
	if (m_iChoiceItem == CMultiChoiceDef::eMultiChoiceEmpty)
	{
		return ft_fieldempty;
	}

	if (m_iChoiceItem == CMultiChoiceDef::eMultiChoiceError || 
		m_iChoiceItem == CMultiChoiceDef::eMultiChoiceInvalidIndex ||
		iMaxBuf < 1 || !ppBuf || !*ppBuf)
	{
		return ft_fileerror;
	}

	strncpy((char*)*ppBuf, m_oDef.getChoiceName(m_iChoiceItem), iMaxBuf);
	((char*)*ppBuf)[iMaxBuf - 1] = '\0';

	return getType().getType();
}
