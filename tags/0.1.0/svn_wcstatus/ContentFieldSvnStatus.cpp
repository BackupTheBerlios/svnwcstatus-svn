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

#include "ContentFieldSvnStatus.h"
#include "SvnFieldLoader.h"
#include "MultiChoiceDefStatus.h"
#include "ContentInstanceMultiChoice.h"

#include "SvnPool.h"

#pragma warning(disable: 4355)  // 'this' : used in base member initializer list
CContentFieldSvnStatus::CContentFieldSvnStatus(CSvnFieldLoader& oLoader) :
	CContentFieldSvnMultiChoice(oLoader, new CMultiChoiceDefStatus(*this))
{
}
#pragma warning(default: 4355)

CContentFieldSvnStatus::~CContentFieldSvnStatus()
{
}

CContentInstance* CContentFieldSvnStatus::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	return new CContentInstanceMultiChoice(*getMultiChoiceDef(), pchPath, getStatusValue(pStatus));
}
