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
