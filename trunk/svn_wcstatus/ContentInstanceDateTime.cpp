#include "ContentInstanceDateTime.h"
#include "ContentField.h"

CContentInstanceDateTime::CContentInstanceDateTime(const CContentField& oField, const char* pchPath, const FILETIME& ftValue) :
	CContentInstance(oField, pchPath),
	m_ftValue(ftValue)
{
}

CContentInstanceDateTime::~CContentInstanceDateTime()
{
}

int CContentInstanceDateTime::copyValueTo(void** ppBuf, int iMaxBuf) const
{
	if (iMaxBuf < sizeof(m_ftValue) || !ppBuf || !*ppBuf)
	{
		return ft_fieldempty;
	}

	*(FILETIME*)*ppBuf = m_ftValue;
	return getType().getType();
}
