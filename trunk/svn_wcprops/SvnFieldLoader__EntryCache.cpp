#include "SvnFieldLoader__EntryCache.h"

#include "apr_hash.h"
#include "svn_pools.h"
#include "svn_wc.h"

CSvnFieldLoader::CEntryCache::CEntryCache(const char* pchPath) :
	m_pPool(svn_pool_create(NULL)),
	m_pchPath(apr_pstrdup(m_pPool, pchPath)),
	m_pEntries(apr_hash_make(m_pPool))
{
}

CSvnFieldLoader::CEntryCache::CEntryCache(apr_pool_t* pPool, const char* pchPath) :
	m_pPool(svn_pool_create(pPool)),
	m_pchPath(apr_pstrdup(pPool, pchPath)),
	m_pEntries(apr_hash_make(m_pPool))
{
}

CSvnFieldLoader::CEntryCache::~CEntryCache()
{
	if (m_pPool)
	{
		svn_pool_destroy(m_pPool);
	}
}


CSvnFieldLoader::CEntryCache* CSvnFieldLoader::CEntryCache::pcreate(apr_pool_t* pPool, const char* pchPath)
{
	void* pData = apr_palloc(pPool, sizeof(CEntryCache));
	CEntryCache oCache(pPool, pchPath);

	memcpy(pData, &oCache, sizeof(CEntryCache));
	oCache.m_pPool = NULL;

	return static_cast<CEntryCache*>(pData);
}

const char* CSvnFieldLoader::CEntryCache::getPath() const
{
	return m_pchPath;
}

bool CSvnFieldLoader::CEntryCache::isPath(const char* pchPath) const
{
	return pchPath && apr_strnatcmp(m_pchPath, pchPath) == 0;
}

svn_wc_status2_t* CSvnFieldLoader::CEntryCache::getEntry(const char* pchEntryName) const
{
	return static_cast<svn_wc_status2_t*>(apr_hash_get(m_pEntries, pchEntryName, APR_HASH_KEY_STRING));
}

void CSvnFieldLoader::CEntryCache::putEntry(svn_wc_status2_t* pEntry, const char* pchName)
{
	svn_wc_status2_t* pMy = svn_wc_dup_status2(pEntry, m_pPool);
	apr_hash_set(m_pEntries, pchName ? apr_pstrdup(m_pPool, pchName) : pMy->entry->name, APR_HASH_KEY_STRING, pMy);
}

void CSvnFieldLoader::CEntryCache::clear(const char* pchNewPath)
{
	if (pchNewPath && pchNewPath != m_pchPath)
	{
		apr_pool_clear(m_pPool);
		m_pchPath = apr_pstrdup(m_pPool, pchNewPath);
	}
	else
	{
		char* pchPath = strdup(m_pchPath);
		apr_pool_clear(m_pPool);
		m_pchPath = apr_pstrdup(m_pPool, pchPath);
		free(pchPath);
	}

	m_pEntries = apr_hash_make(m_pPool);
}
