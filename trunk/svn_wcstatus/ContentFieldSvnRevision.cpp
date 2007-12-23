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

#include "ContentFieldSvnRevision.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceNumeric32.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnRevision::CContentFieldSvnRevision(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnRevision::~CContentFieldSvnRevision()
{
}

const char* CContentFieldSvnRevision::getName() const
{
	return "svn-revision";
}

int CContentFieldSvnRevision::getType() const
{
	return ft_numeric_32;
}

CContentInstance* CContentFieldSvnRevision::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceNumeric32(*this, pchPath, pStatus->entry->revision);
}
