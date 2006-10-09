#include "SvnFieldLoader.h"
#include "SvnFieldLoader__EntryCache.h"
#include "ContentFieldSvnRevision.h"
#include "ContentFieldSvnCmtAuthor.h"
#include "ContentFieldSvnCmtRev.h"
#include "ContentFieldSvnCmtTime.h"
#include "ContentFieldSvnStatusText.h"
#include "ContentFieldSvnStatusProps.h"
#include "ContentFieldSvnSchedule.h"
#include "ContentFieldSvnUrl.h"
#include "ContentFieldSvnRepos.h"
#include "ContentFieldSvnUuid.h"
#include "ContentFieldSvnCopied.h"
#include "ContentFieldSvnDeleted.h"
#include "ContentFieldSvnAbsent.h"
#include "ContentFieldSvnIncomplete.h"

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
	}
}

CSvnFieldLoader::CSvnFieldLoader() :
	m_pFields(new CContentField*[15]),
	m_nFieldCount(0),
	m_oPool(),
	m_pLastEntry(NULL)
{
	m_pFields[m_nFieldCount++] = new CContentFieldSvnRevision(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnCmtAuthor(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnCmtRev(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnCmtTime(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnStatusText(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnStatusProps(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnSchedule(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnUrl(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnRepos(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnUuid(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnCopied(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnDeleted(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnAbsent(*this);
	m_pFields[m_nFieldCount++] = new CContentFieldSvnIncomplete(*this);
	m_pFields[m_nFieldCount] = NULL;

	SVN_EX(svn_client_create_context(&m_pClientCtx, m_oPool));
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
	CSvnPool oSubpool(m_oPool);
	svn_wc_status2_t* pRet = NULL;

	const char* pchInternalPath = svn_path_internal_style(pchPath, oSubpool);
	const char* pchDir = svn_path_dirname(pchInternalPath, oSubpool);
	const char* pchBaseName = svn_path_basename(pchInternalPath, oSubpool);

	if (m_pLastEntry)
	{
		if (m_pLastEntry->isPath(pchDir))
		{
			return dupEntry(m_pLastEntry->getEntry(pchBaseName), pPool);
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
	sBaton.pTempPool = (apr_pool_t*)oSubpool;

	SVN_EX(svn_client_status2(NULL, pchDir, &rev, statusFunc, &sBaton, FALSE,
	                          TRUE, FALSE, TRUE, TRUE, m_pClientCtx, oSubpool));

	return dupEntry(m_pLastEntry->getEntry(pchBaseName), pPool);
}

void CSvnFieldLoader::aprTimeToFileTime(apr_time_t nTime, FILETIME& ftTime) const
{
	apr_time_exp_t sAprTime;
	SYSTEMTIME sSysTime;

	apr_time_exp_gmt(&sAprTime, nTime);

	sSysTime.wMilliseconds = sAprTime.tm_usec / 1000;
	sSysTime.wSecond       = sAprTime.tm_sec;
	sSysTime.wMinute       = sAprTime.tm_min;
	sSysTime.wHour         = sAprTime.tm_hour;
	sSysTime.wDay          = sAprTime.tm_mday;
	sSysTime.wMonth        = sAprTime.tm_mon + 1;
	sSysTime.wYear         = sAprTime.tm_year + 1900;

	SystemTimeToFileTime(&sSysTime, &ftTime);
}

svn_wc_status2_t* CSvnFieldLoader::dupEntry(svn_wc_status2_t* pEntry, apr_pool_t* pPool)
{
	return pEntry ? svn_wc_dup_status2(pEntry, pPool) : NULL;
}
