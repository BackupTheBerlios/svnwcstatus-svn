#include "SvnFieldLoader.h"
#include "SvnFieldLoader__Parameters.h"
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
#include "ContentFieldSvnTextTime.h"
#include "ContentFieldSvnPropTime.h"
#include "ContentFieldSvnLockToken.h"
#include "ContentFieldSvnLockOwner.h"
#include "ContentFieldSvnLockComment.h"
#include "ContentFieldSvnLockCreationDate.h"

#include "svn_pools.h"
#include "svn_path.h"
#include "svn_client.h"

#define INITIAL_FIELD_ARRAY_SIZE 30

struct SvnFieldLoaderStatusBaton
{
	CSvnFieldLoader::CEntryCache* pCache;
	apr_pool_t* pTempPool;
};

static void statusFunc(void* pBaton, const char* pchPath, svn_wc_status2_t *pStatus)
{
	if (pStatus)
	{
		SvnFieldLoaderStatusBaton* pData = static_cast<SvnFieldLoaderStatusBaton*>(pBaton);
		const char* pchInternalFile = svn_path_internal_style(pchPath, pData->pTempPool);
		const char* pchBaseName = svn_path_basename(pchInternalFile, pData->pTempPool);
		pData->pCache->putEntry(pStatus, pchBaseName);
	}
}

static int cleanupFieldArray(void* pData)
{
	apr_array_header_t* pArray = static_cast<apr_array_header_t*>(pData);

	for (int i = 0; i < pArray->nelts; ++i)
	{
		delete APR_ARRAY_GET(pArray, i, CContentFieldSvn*);
	}

	return APR_SUCCESS;
}

CSvnFieldLoader::CSvnFieldLoader() :
	m_oPool(),
	m_pFields(NULL),
	m_pClientCtx(NULL),
	m_pParams(NULL),
	m_pLastEntry(NULL)
{
	SVN_EX(svn_client_create_context(&m_pClientCtx, m_oPool));
	emptyContentFields(0);
}

CSvnFieldLoader::~CSvnFieldLoader()
{
	if (m_pLastEntry)
	{
		delete m_pLastEntry;
	}

	if (m_pParams)
	{
		delete m_pParams;
	}
}

CContentField& CSvnFieldLoader::getFieldByIndex(int iIdx)
{
	if (iIdx < 0 || (size_t)iIdx >= getFieldCount())
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchFieldIndex);
	}

	return *getField(iIdx);
}

size_t CSvnFieldLoader::getFieldCount() const
{
	return m_pFields ? m_pFields->nelts : 0;
}

void CSvnFieldLoader::initParameters(const ContentDefaultParamStruct& sParams)
{
	if (m_pParams)
	{
		delete m_pParams;
	}

	m_pParams = new CParameters(sParams);

	emptyContentFields(INITIAL_FIELD_ARRAY_SIZE);
	appendDefaultContentFields();
}

CContentFieldSvn* CSvnFieldLoader::getField(int iIdx)
{
	return APR_ARRAY_GET(m_pFields, iIdx, CContentFieldSvn*);
}

void CSvnFieldLoader::appendField(CContentFieldSvn* pField)
{
	APR_ARRAY_APPEND(m_pFields, pField, CContentFieldSvn*);
}

void CSvnFieldLoader::emptyContentFields(int iInitialArrayLen)
{
	apr_pool_t* pPool;

	if (!m_pFields)
	{
		pPool = svn_pool_create(m_oPool);
	}
	else
	{
		pPool = m_pFields->pool;
		svn_pool_clear(pPool);
	}

	m_pFields = apr_array_make(pPool, iInitialArrayLen, sizeof (CContentFieldSvn*));
	apr_pool_cleanup_register(m_pFields->pool, m_pFields, cleanupFieldArray, NULL);
}

void CSvnFieldLoader::appendDefaultContentFields()
{
	appendField(new CContentFieldSvnRevision(*this));
	appendField(new CContentFieldSvnRevision(*this));
	appendField(new CContentFieldSvnCmtAuthor(*this));
	appendField(new CContentFieldSvnCmtRev(*this));
	appendField(new CContentFieldSvnCmtTime(*this));
	appendField(new CContentFieldSvnStatusText(*this));
	appendField(new CContentFieldSvnStatusProps(*this));
	appendField(new CContentFieldSvnSchedule(*this));
	appendField(new CContentFieldSvnUrl(*this));
	appendField(new CContentFieldSvnRepos(*this));
	appendField(new CContentFieldSvnUuid(*this));
	appendField(new CContentFieldSvnCopied(*this));
	appendField(new CContentFieldSvnDeleted(*this));
	appendField(new CContentFieldSvnAbsent(*this));
	appendField(new CContentFieldSvnIncomplete(*this));
	appendField(new CContentFieldSvnTextTime(*this));
	appendField(new CContentFieldSvnPropTime(*this));
	appendField(new CContentFieldSvnLockToken(*this));
	appendField(new CContentFieldSvnLockOwner(*this));
	appendField(new CContentFieldSvnLockComment(*this));
	appendField(new CContentFieldSvnLockCreationDate(*this));
}

svn_wc_status2_t* CSvnFieldLoader::getStatusForPath(const char* pchPath, apr_pool_t* pPool)
{
	CSvnPool oSubpool(m_oPool);
	svn_wc_status2_t* pRet = NULL;

	const char* pchInternalPath = svn_path_internal_style(pchPath, oSubpool);
	const char* pchBaseName = svn_path_basename(pchInternalPath, oSubpool);

	if (svn_wc_is_adm_dir(pchBaseName, oSubpool))
	{
		return NULL;
	}

	const char* pchDir = svn_path_dirname(pchInternalPath, oSubpool);

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
	// XXX error handling?

	apr_time_exp_t sAprTime = {0};
	apr_time_exp_gmt(&sAprTime, nTime);

	SYSTEMTIME sSysTime = 
	{
		sAprTime.tm_year + 1900,  // wYear
		sAprTime.tm_mon + 1,      // wMonth
		0,                        // wDayOfWeek
		sAprTime.tm_mday,         // wDay
		sAprTime.tm_hour,         // wHour
		sAprTime.tm_min,          // wMinute
		sAprTime.tm_sec,          // wSecond
		sAprTime.tm_usec / 1000   // wMilliseconds
	};

	SystemTimeToFileTime(&sSysTime, &ftTime);
}

svn_wc_status2_t* CSvnFieldLoader::dupEntry(svn_wc_status2_t* pEntry, apr_pool_t* pPool)
{
	return pEntry ? svn_wc_dup_status2(pEntry, pPool) : NULL;
}

#undef INITIAL_FIELD_ARRAY_SIZE
