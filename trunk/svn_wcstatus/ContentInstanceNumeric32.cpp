#include "ContentInstanceNumeric32.h"
#include "ContentField.h"

CContentInstanceNumeric32::CContentInstanceNumeric32(const CContentField& oField, const char* pchPath, int nValue) :
	CContentInstance(oField, pchPath),
	m_nValue(nValue)
{
}

CContentInstanceNumeric32::~CContentInstanceNumeric32()
{
}

int CContentInstanceNumeric32::copyValueTo(void** ppBuf, int iMaxBuf) const
{
	if (iMaxBuf < sizeof(m_nValue) || !ppBuf || !*ppBuf)
	{
		return ft_fieldempty;
	}

	*(int*)*ppBuf = m_nValue;
	return getType().getType();
}
