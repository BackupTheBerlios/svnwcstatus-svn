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

#include "SvnPool.h"

#include "svn_pools.h"

CSvnPool::CSvnPool() :
	m_pPool(svn_pool_create(NULL))
{
}

CSvnPool::CSvnPool(CSvnPool& oParent) :
	m_pPool(svn_pool_create(oParent.m_pPool))
{
}

CSvnPool::CSvnPool(apr_pool_t* pParent) :
	m_pPool(svn_pool_create(pParent))
{
}

CSvnPool::~CSvnPool()
{
	if (m_pPool) apr_pool_destroy(m_pPool);
}

apr_pool_t* CSvnPool::replace(apr_pool_t* pPool)
{
	apr_pool_t* pTemp = m_pPool;
	m_pPool = pPool;
	return pTemp;
}

CSvnPool& CSvnPool::clear()
{
	svn_pool_clear(m_pPool);
	return *this;
}

void CSvnPool::destroy()
{
	svn_pool_destroy(m_pPool);
	m_pPool = NULL;
}

apr_pool_t* CSvnPool::release()
{
	return replace(NULL);
}

CSvnPool::operator apr_pool_t*()
{
	return m_pPool;
}
