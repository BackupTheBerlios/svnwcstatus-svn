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

CSvnPool& CSvnPool::clear()
{
	apr_pool_clear(m_pPool);
	return *this;
}

void CSvnPool::destroy()
{
	apr_pool_destroy(m_pPool);
	release();
}

void CSvnPool::release()
{
	m_pPool = NULL;
}

CSvnPool::operator apr_pool_t*()
{
	return m_pPool;
}
