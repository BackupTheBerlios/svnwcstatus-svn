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

#include "ContentFieldSvnProp.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "apr_hash.h"
#include "svn_subst.h"
#include "svn_client.h"

CContentFieldSvnProp::CContentFieldSvnProp(CSvnFieldLoader& oLoader, const char* pchPropName, const char* pchFieldName) :
	CContentFieldSvn(oLoader),
	m_oPool(),
	m_pchPropName(apr_pstrdup(m_oPool, pchPropName)),
	m_pchFieldName(apr_pstrdup(m_oPool, pchFieldName))
{
}

CContentFieldSvnProp::~CContentFieldSvnProp()
{
}

const char* CContentFieldSvnProp::getName() const
{
	return m_pchFieldName;
}

int CContentFieldSvnProp::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnProp::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	apr_hash_t* pProps = getParent().getPropsForPath(pchPath, oPool);

	if (!pProps)
	{
		return new CContentInstanceEmpty(*this, pchPath);
	}

	svn_string_t* pValue = static_cast<svn_string_t*>(apr_hash_get(pProps, m_pchPropName, APR_HASH_KEY_STRING));

	if (pValue)
	{
		if (svn_prop_needs_translation(m_pchPropName))
		{
			svn_subst_detranslate_string(&pValue, pValue, TRUE, oPool);
		}

		return new CContentInstanceString(*this, pchPath, pValue->data, pValue->len);
	}
	else
	{
		return new CContentInstanceEmpty(*this, pchPath);
	}
}
