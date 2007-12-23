/* Copyright 2007, 2008 Tom Wieczorek
 *
 * This file is part of svn_wcstatus.
 *
 * svn_wcstatus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * svn_wcstatus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with svn_wcstatus. If not, see <http://www.gnu.org/licenses/>.
 */

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
