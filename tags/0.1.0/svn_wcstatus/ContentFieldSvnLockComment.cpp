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

#include "ContentFieldSvnLockComment.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnLockComment::CContentFieldSvnLockComment(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnLockComment::~CContentFieldSvnLockComment()
{
}

const char* CContentFieldSvnLockComment::getName() const
{
	return "svn-lock-comment";
}

int CContentFieldSvnLockComment::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnLockComment::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return pStatus->entry && pStatus->entry->lock_comment ? 
		static_cast<CContentInstance*>(new CContentInstanceString(*this, pchPath, pStatus->entry->lock_comment)) :
		static_cast<CContentInstance*>(new CContentInstanceEmpty(*this, pchPath));
}
