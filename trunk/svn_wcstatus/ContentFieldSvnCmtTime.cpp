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

#include "ContentFieldSvnCmtTime.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceDateTime.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnCmtTime::CContentFieldSvnCmtTime(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnCmtTime::~CContentFieldSvnCmtTime()
{
}

const char* CContentFieldSvnCmtTime::getName() const
{
	return "svn-cmt-time";
}

int CContentFieldSvnCmtTime::getType() const
{
	return ft_datetime;
}

CContentInstance* CContentFieldSvnCmtTime::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	FILETIME ftTime;
	getParent().aprTimeToFileTime(pStatus->entry->cmt_date, ftTime);

	return new CContentInstanceDateTime(*this, pchPath, ftTime);
}
