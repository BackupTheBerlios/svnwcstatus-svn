#include "ContentInstanceString.h"
#include "ContentField.h"

CContentInstanceString::CContentInstanceString(const CContentField& oField, const char* pchPath, const char* pchValue) :
	CContentInstance(oField, pchPath),
	m_achValue(NULL)
{
	if (pchValue && *pchValue != '\0')
	{
		const size_t nLen = strlen(pchValue);
		m_achValue = new char[nLen + 1];
		strcpy(m_achValue, pchValue);
		m_achValue[nLen] = '\0';
	}
}

CContentInstanceString::CContentInstanceString(const CContentField& oField, const char* pchPath, const char* pchValue, size_t nLen) :
	CContentInstance(oField, pchPath),
	m_achValue(nLen && pchValue ? strncpy(new char[nLen + 1], pchValue, nLen) : NULL)
{
	if (m_achValue)
	{
		m_achValue[nLen] = '\0';
	}
}

CContentInstanceString::~CContentInstanceString()
{
	if (m_achValue)
	{
		delete [] m_achValue;
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
