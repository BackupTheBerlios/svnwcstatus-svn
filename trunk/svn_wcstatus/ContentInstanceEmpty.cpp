#include "ContentInstanceEmpty.h"

CContentInstanceEmpty::CContentInstanceEmpty(const CContentField& oField, const char* pchFile) :
	CContentInstance(oField, pchFile)
{
}

CContentInstanceEmpty::~CContentInstanceEmpty()
{
}

int CContentInstanceEmpty::copyValueTo(void** ppBuf, int iMaxBuf) const
{
	return ft_fieldempty;
}
