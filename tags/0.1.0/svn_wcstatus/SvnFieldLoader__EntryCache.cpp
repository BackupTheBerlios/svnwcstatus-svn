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

#include "SvnFieldLoader__EntryCache.h"
#include "SvnFieldLoader__Parameters.h"

#include "apr_tables.h"
#include "apr_hash.h"
#include "svn_pools.h"
#include "svn_path.h"
#include "svn_wc.h"
#include "svn_client.h"

class CSvnFieldLoader::CEntryCache::CStatusWalker
{
public:
	CStatusWalker(CEntryCache* pCaller, apr_hash_t* pStatuses, bool bTweakExtStatus) :
		m_oTempPool(),
		m_pCaller(pCaller),
		m_bTweakExtStatuses(bTweakExtStatus),
		m_pStatuses(pStatuses)
	{
	}

	static void statusCallback(void* pWalker, const char* pchPath, svn_wc_status2_t* pStatus)
	{
		if (pWalker && pchPath && pStatus)
			static_cast<CStatusWalker*>(pWalker)->processStatus(pchPath, pStatus);
	}

private:
	void processStatus(const char* pchPath, svn_wc_status2_t* pStatus)
	{
		const char* pchInternalFile = svn_path_internal_style(pchPath, m_oTempPool);

		apr_pool_t* pStatusPool = apr_hash_pool_get(m_pStatuses);
		const char* pchBaseName = svn_path_basename(pchInternalFile, pStatusPool);

		if (m_bTweakExtStatuses && pStatus->text_status == svn_wc_status_external)
		{
			m_pCaller->makeExternalStatus(pStatus, pchPath, pStatusPool, m_oTempPool);
		}
		else
		{
			pStatus = svn_wc_dup_status2(pStatus, pStatusPool);
		}

		apr_hash_set(m_pStatuses, apr_pstrdup(pStatusPool, pchBaseName), APR_HASH_KEY_STRING, pStatus);

		m_oTempPool.clear();
	}

private:
	CSvnPool m_oTempPool;
	CEntryCache* m_pCaller;
	bool m_bTweakExtStatuses;
	apr_hash_t* m_pStatuses;
};

CSvnFieldLoader::CEntryCache::CEntryCache(CSvnFieldLoader& oParent, const char* pchPath) :
	m_oPool(),
	m_oParent(oParent),
	m_pchPath(apr_pstrdup(m_oPool, pchPath)),
	m_pAdm(NULL),
	m_pStatuses(NULL),
	m_pProps(NULL)
{
}

CSvnFieldLoader::CEntryCache::~CEntryCache()
{
}

const char* CSvnFieldLoader::CEntryCache::getPath() const
{
	return m_pchPath;
}

apr_hash_t* CSvnFieldLoader::CEntryCache::getStatuses()
{
	if (!m_pStatuses) collectStatuses();
	return m_pStatuses;
}

apr_hash_t* CSvnFieldLoader::CEntryCache::getProps()
{
	if (!m_pProps) collectProps();
	return m_pProps;
}

svn_wc_adm_access_t* CSvnFieldLoader::CEntryCache::getAdm()
{
	if (!m_pAdm) openAdm();
	return m_pAdm;
}

bool CSvnFieldLoader::CEntryCache::isPath(const char* pchPath) const
{
	return pchPath && apr_strnatcmp(m_pchPath, pchPath) == 0;
}

svn_wc_status2_t* CSvnFieldLoader::CEntryCache::getStatus(const char* pchEntryName)
{
	return static_cast<svn_wc_status2_t*>(apr_hash_get(getStatuses(), pchEntryName, APR_HASH_KEY_STRING));
}

apr_hash_t* CSvnFieldLoader::CEntryCache::getProps(const char* pchEntryName)
{
	return static_cast<apr_hash_t*>(apr_hash_get(getProps(), pchEntryName, APR_HASH_KEY_STRING));
}

CSvnFieldLoader::CEntryCache* CSvnFieldLoader::CEntryCache::switchPath(const char* pchNewPath)
{
	if (pchNewPath && pchNewPath != m_pchPath)
	{
		m_oPool.clear();
		m_pchPath = apr_pstrdup(m_oPool, pchNewPath);
	}
	else
	{
		char* pchPath = strdup(m_pchPath);
		m_oPool.clear();
		m_pchPath = apr_pstrdup(m_oPool, pchPath);
		free(pchPath);
	}

	m_pAdm = NULL;
	m_pStatuses = NULL;
	m_pProps = NULL;

	return this;
}

void CSvnFieldLoader::CEntryCache::openAdm()
{
	m_pAdm = openAdmFor(m_pchPath, 1, m_oPool);
}

svn_wc_adm_access_t* CSvnFieldLoader::CEntryCache::openAdmFor(const char* pchPath, int iDepth, apr_pool_t* pPool)
{
	svn_wc_adm_access_t* pAdm;
	SVN_EX(svn_wc_adm_open3(&pAdm, NULL, pchPath, FALSE, iDepth,
	                        m_oParent.m_pClientCtx->cancel_func,
	                        m_oParent.m_pClientCtx->cancel_baton, pPool));
	return pAdm;
}

void CSvnFieldLoader::CEntryCache::collectStatuses()
{
	CSvnPool oTempPool;
	svn_wc_adm_access_t* pAdm = getAdm();

	CSvnPool oStatusPool(m_oPool);
	apr_hash_t* pStatuses = apr_hash_make(oStatusPool);
	CStatusWalker oWalker(this, pStatuses, m_oParent.m_pParams->shouldTweakExternalStatus());

	const svn_delta_editor_t *pEditor;
	void* pEditBaton;
	svn_wc_traversal_info_t* pTravInfo = svn_wc_init_traversal_info(oTempPool);

	SVN_EX(svn_wc_get_status_editor2(&pEditor, &pEditBaton, NULL, NULL, pAdm, "",
	                                 m_oParent.m_pClientCtx->config, FALSE, TRUE,
	                                 TRUE, CStatusWalker::statusCallback, &oWalker,
	                                 m_oParent.m_pClientCtx->cancel_func,
	                                 m_oParent.m_pClientCtx->cancel_baton,
	                                 pTravInfo, oTempPool));

	SVN_EX(pEditor->close_edit(pEditBaton, oTempPool));

	// store results and don't destroy oStatusPool
	m_pStatuses = pStatuses;
	oStatusPool.release();
}

void CSvnFieldLoader::CEntryCache::collectProps()
{
	CSvnPool oTempPool;
	svn_wc_adm_access_t* pAdm = getAdm();
	apr_hash_t* pEntries;

	SVN_EX(svn_wc_entries_read(&pEntries, pAdm, FALSE, oTempPool));

	CSvnPool oPropsPool(m_oPool);
	apr_hash_t* pProps = apr_hash_make(oPropsPool);

	for (apr_hash_index_t* pIdx = apr_hash_first(oTempPool, pEntries); pIdx; pIdx = apr_hash_next(pIdx))
	{
		const char* pchEntryName;
		apr_hash_t* pThisProps;

		apr_hash_this(pIdx, reinterpret_cast<const void**>(&pchEntryName), NULL, NULL);

		if (apr_strnatcmp(pchEntryName, SVN_WC_ENTRY_THIS_DIR) == 0) continue;

		SVN_EX(svn_wc_prop_list(&pThisProps, svn_path_join(m_pchPath, pchEntryName, oTempPool), pAdm, oPropsPool));
		apr_hash_set(pProps, pchEntryName, APR_HASH_KEY_STRING, pThisProps);
	}

	// store results and don't destroy oPropsPool
	m_pProps = pProps;
	oPropsPool.release();
}

void CSvnFieldLoader::CEntryCache::makeExternalStatus(svn_wc_status2_t*& pStatus, const char* pchPath, apr_pool_t* pStatusPool, apr_pool_t* pTempPool)
{
	svn_wc_adm_access_t* pExtAdm = openAdmFor(pchPath, 0, pTempPool);
	SVN_EX(svn_wc_status2(&pStatus, pchPath, pExtAdm, pStatusPool));
	pStatus->text_status = svn_wc_status_external;
}
