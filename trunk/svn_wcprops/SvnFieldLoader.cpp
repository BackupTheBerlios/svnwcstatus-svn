#include "SvnFieldLoader.h"
#include "SvnFieldLoader__EntryCache.h"
#include "ContentFieldSvnAuthor.h"
#include "ContentFieldSvnIgnored.h"
#include "ContentFieldSvnSchedule.h"

#include "svn_pools.h"
#include "svn_path.h"
#include "svn_client.h"

struct SvnFieldLoaderStatusBaton
{
	CSvnFieldLoader::CEntryCache* pCache;
	apr_pool_t* pTempPool;
};

static void statusFunc(void* pBaton, const char* pchPath, svn_wc_status2_t *pStatus)
{
	SvnFieldLoaderStatusBaton* pData = static_cast<SvnFieldLoaderStatusBaton*>(pBaton);

	if (pStatus)
	{
		const char* pchInternalFile = svn_path_internal_style(pchPath, pData->pTempPool);
		const char* pchBaseName = svn_path_basename(pchInternalFile, pData->pTempPool);
		pData->pCache->putEntry(pStatus, pchBaseName);
		apr_pool_clear(pData->pTempPool);
	}
}

CSvnFieldLoader::CSvnFieldLoader() :
	m_pFields(new CContentField*[4]),
	m_nFieldCount(0),
	m_pPool(svn_pool_create(NULL)),
	m_pLastEntry(NULL)
{
	m_pFields[m_nFieldCount++] = new CContentFieldSvnAuthor(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnIgnored(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnSchedule(*this);
	m_pFields[m_nFieldCount] = NULL;

	SVN_EX(svn_client_create_context(&m_pClientCtx, m_pPool));
}

CSvnFieldLoader::~CSvnFieldLoader()
{
	for (CContentField* pField = *m_pFields; pField; ++pField)
	{
		delete pField;
	}

	delete [] m_pFields;

	if (m_pLastEntry)
	{
		delete m_pLastEntry;
	}

	svn_pool_destroy(m_pPool);
}

CContentField& CSvnFieldLoader::getFieldByIndex(int iIdx)
{
	if (iIdx < 0 || (size_t)iIdx >= m_nFieldCount)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchFieldIndex);
	}

	return *(m_pFields[iIdx]);
}

svn_wc_status2_t* CSvnFieldLoader::getStatusForPath(const char* pchPath, apr_pool_t* pPool)
{
	apr_pool_t* pSubpool = svn_pool_create(m_pPool);
	svn_wc_status2_t* pRet = NULL;

	do try
	{
		const char* pchInternalPath = svn_path_internal_style(pchPath, pSubpool);
		const char* pchDir = svn_path_dirname(pchInternalPath, pSubpool);
		const char* pchBaseName = svn_path_basename(pchInternalPath, pSubpool);

		if (m_pLastEntry)
		{
			if (m_pLastEntry->isPath(pchDir))
			{
				pRet= m_pLastEntry->getEntry(pchBaseName);
				break;
			}

			m_pLastEntry->clear(pchDir);
		}
		else
		{
			m_pLastEntry = new CEntryCache(pchDir);
		}

		svn_opt_revision_t rev;
		rev.kind = svn_opt_revision_head;

		SvnFieldLoaderStatusBaton sBaton;
		sBaton.pCache = m_pLastEntry;
		sBaton.pTempPool = svn_pool_create(pSubpool);

		SVN_EX(svn_client_status2(NULL, pchDir, &rev, statusFunc, &sBaton, FALSE,
		                          TRUE, FALSE, TRUE, TRUE, m_pClientCtx, pSubpool));

		pRet = m_pLastEntry->getEntry(pchBaseName);
	}
	catch (...)
	{
		svn_pool_destroy(pSubpool);
		throw;
	} while (false);


	svn_pool_destroy(pSubpool);
	return pRet ? svn_wc_dup_status2(pRet, pPool) : NULL;
}
