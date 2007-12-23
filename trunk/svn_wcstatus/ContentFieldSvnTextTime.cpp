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

#include "ContentFieldSvnTextTime.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceDateTime.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnTextTime::CContentFieldSvnTextTime(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnTextTime::~CContentFieldSvnTextTime()
{
}

const char* CContentFieldSvnTextTime::getName() const
{
	return "svn-text-time";
}

int CContentFieldSvnTextTime::getType() const
{
	return ft_datetime;
}

CContentInstance* CContentFieldSvnTextTime::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	if (pStatus->entry && pStatus->entry->text_time != 0)
	{
		FILETIME ftTime;
		getParent().aprTimeToFileTime(pStatus->entry->text_time, ftTime);
		return new CContentInstanceDateTime(*this, pchPath, ftTime);
	}

	return new CContentInstanceEmpty(*this, pchPath);
}
