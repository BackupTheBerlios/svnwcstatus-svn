#include "ContentInstanceString.h"
#include "ContentField.h"

CContentInstanceString::CContentInstanceString(const CContentField& oField, const char* pchFile, const char* pchValue) :
	CContentInstance(oField, pchFile),
	m_pchValue(pchValue && *pchValue != '\0' ? strdup(pchValue) : NULL)
{
}

CContentInstanceString::~CContentInstanceString()
{
	if (m_pchValue)
		free(m_pchValue);
}

int CContentInstanceString::copyValueTo(void** ppBuf, int iMaxBuf) const
{
	if (!m_pchValue)
	{
		return ft_fieldempty;
	}

	if (iMaxBuf > 0 && ppBuf && *ppBuf)
	{
		strncpy((char*)*ppBuf, m_pchValue, iMaxBuf);
		((char*)*ppBuf)[iMaxBuf - 1] = '\0';
	}

	return getType().getType();
}
