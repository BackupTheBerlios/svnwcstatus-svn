#include "ContentInstanceBoolean.h"
#include "ContentField.h"

CContentInstanceBoolean::CContentInstanceBoolean(const CContentField& oField, const char* pchFile) :
	CContentInstance(oField, pchFile),
	m_nValue(-1)
{
}

CContentInstanceBoolean::CContentInstanceBoolean(const CContentField& oField, const char* pchFile, bool bValue) :
	CContentInstance(oField, pchFile),
	m_nValue(bValue ? 1 : 0)
{
}

CContentInstanceBoolean::CContentInstanceBoolean(const CContentField& oField, const char* pchFile, bool* pbValue) :
	CContentInstance(oField, pchFile),
	m_nValue(pbValue ? (*pbValue ? 1 : 0) : -1)
{
}

CContentInstanceBoolean::~CContentInstanceBoolean()
{
}

int CContentInstanceBoolean::copyValueTo(void** ppBuf, int iMaxBuf) const
{
	if (m_nValue == -1 || iMaxBuf < sizeof(int) || !ppBuf || !*ppBuf)
	{
		return ft_fieldempty;
	}

	*(int*)*ppBuf = m_nValue ? 1 : 0;
	return getType().getType();
}
