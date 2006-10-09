#include "ContentField.h"
#include "MultiChoiceDef.h"

CContentField::~CContentField()
{
}

int CContentField::fillInDefinition(char* pchName, char* pchUnits, int iMaxBuf) const
{
	if (iMaxBuf < 1) return getType();
		
	if (pchName)
	{
		strncpy(pchName, getName(), iMaxBuf);
		pchName[iMaxBuf - 1] = '\0';
	}

	if (pchUnits)
	{
		if (hasMultiChoiceDef())
		{
			getUnits(pchUnits, iMaxBuf);
		}
		else
		{
			*pchUnits = '\0';
		}
	}

	return getType();
}

bool CContentField::hasMultiChoiceDef() const
{
	return getMultiChoiceDef() != NULL;
}

const CMultiChoiceDef* CContentField::getMultiChoiceDef() const
{
	return NULL;
}

void CContentField::getUnits(char* pchUnits, int iMaxBuf) const
{
	const CMultiChoiceDef* pDef = getMultiChoiceDef();

	if (!pDef) return;

	const size_t nUnitCount = pDef->getChoiceCount();

	for (size_t i = 1, nBufLeft = iMaxBuf; i <= nUnitCount && nBufLeft; ++i)
	{
		const char* pchCurUnit = pDef->getChoiceName(i);
		const size_t nCurLen = strlen(pchCurUnit);
		const size_t nCopyLen = nBufLeft > nCurLen ? nCurLen : nBufLeft;
		strncpy(pchUnits, pchCurUnit, nCopyLen);
		pchUnits += nCopyLen;
		nBufLeft -= nCopyLen;

		if (nBufLeft)
		{
			*pchUnits++ = '|';
			--nBufLeft;
		}
	}

	if (nUnitCount)	*--pchUnits = '\0';
}
