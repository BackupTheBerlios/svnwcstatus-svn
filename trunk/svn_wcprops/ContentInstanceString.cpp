#include "ContentInstanceString.h"
#include "ContentField.h"

CContentInstanceString::CContentInstanceString(const CContentField& oField, const char* pchFile, const char* pchValue) :
	CContentInstance(oField, pchFile)
{
	m_achValue = new char[strlen(pchValue) + 1];
	strcpy(m_achValue, pchValue);
}

CContentInstanceString::~CContentInstanceString()
{
	if (m_achValue)
	{
		delete [] m_achValue;
		m_achValue = NULL;
	}
}

int CContentInstanceString::copyValueTo(void** ppBuf, int iMaxBuf) const
{
	if (!m_achValue || *m_achValue == '\0')
	{
		return ft_fieldempty;
	}

	if (iMaxBuf > 0 && ppBuf && *ppBuf)
	{
		strncpy((char*)*ppBuf, m_achValue, iMaxBuf);
		((char*)*ppBuf)[iMaxBuf - 1] = '\0';
	}

	return getType().getType();
}