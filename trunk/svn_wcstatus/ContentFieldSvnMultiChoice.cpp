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

#include "ContentFieldSvnMultiChoice.h"
#include "MultiChoiceDef.h"

CContentFieldSvnMultiChoice::CContentFieldSvnMultiChoice(CSvnFieldLoader& oLoader, CMultiChoiceDef* pDef) :
	CContentFieldSvn(oLoader),
	m_pDef(pDef)
{
}

CContentFieldSvnMultiChoice::~CContentFieldSvnMultiChoice()
{
	delete m_pDef;
}

int CContentFieldSvnMultiChoice::getType() const
{
	return ft_multiplechoice;
}

const CMultiChoiceDef* CContentFieldSvnMultiChoice::getMultiChoiceDef() const
{
	return m_pDef;
}
