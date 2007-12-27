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

#include "ContentFieldSvnPresentProps.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "apr_hash.h"
#include "svn_string.h"
#include "svn_client.h"

CContentFieldSvnPresentProps::CContentFieldSvnPresentProps(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnPresentProps::~CContentFieldSvnPresentProps()
{
}

const char* CContentFieldSvnPresentProps::getName() const
{
	return "svn-present-props";
}

int CContentFieldSvnPresentProps::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnPresentProps::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	apr_hash_t* pProps = getParent().getPropsForPath(pchPath, oPool);

	if (!pProps)
	{
		return new CContentInstanceEmpty(*this, pchPath);
	}

	svn_stringbuf_t* pBuf = svn_stringbuf_create("", oPool);
	svn_stringbuf_ensure(pBuf, apr_hash_count(pProps) * 16);

	for (apr_hash_index_t* pIdx = apr_hash_first(oPool, pProps); pIdx; pIdx = apr_hash_next(pIdx))
	{
		const char* pchPropName;
		int iSize = 0;

		apr_hash_this(pIdx, reinterpret_cast<const void**>(&pchPropName), &iSize, NULL);
		svn_stringbuf_appendcstr(pBuf, pchPropName);
		svn_stringbuf_appendcstr(pBuf, " ");
	}

	svn_stringbuf_chop(pBuf, 1);
	return new CContentInstanceString(*this, pchPath, pBuf->data, pBuf->len);
}
