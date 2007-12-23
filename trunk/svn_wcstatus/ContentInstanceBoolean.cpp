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

#include "ContentInstanceBoolean.h"
#include "ContentField.h"

CContentInstanceBoolean::CContentInstanceBoolean(const CContentField& oField, const char* pchPath) :
	CContentInstance(oField, pchPath),
	m_nValue(-1)
{
}

CContentInstanceBoolean::CContentInstanceBoolean(const CContentField& oField, const char* pchPath, bool bValue) :
	CContentInstance(oField, pchPath),
	m_nValue(bValue ? 1 : 0)
{
}

CContentInstanceBoolean::CContentInstanceBoolean(const CContentField& oField, const char* pchPath, bool* pbValue) :
	CContentInstance(oField, pchPath),
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
