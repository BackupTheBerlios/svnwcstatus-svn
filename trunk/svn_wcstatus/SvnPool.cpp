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
