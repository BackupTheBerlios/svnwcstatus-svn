#include "SvnFieldLoader.h"
#include "ContentFieldSvnAuthor.h"
#include "ContentFieldSvnIgnored.h"
#include "ContentFieldSvnSchedule.h"

#include "svn_pools.h"
#include "svn_path.h"
#include "svn_client.h"

struct SvnFieldLoaderStatusBaton
{
	const char* pchReqFile;
	svn_wc_status2_t* pStatus;
	apr_pool_t* pPool;
};

static void statusFunc(void* pBaton, const char* pchPath, svn_wc_status2_t *pStatus)
{
	SvnFieldLoaderStatusBaton* pData = static_cast<SvnFieldLoaderStatusBaton*>(pBaton);

	if (!pData->pStatus)
	{
		const char* pInternalFile = svn_path_internal_style(pchPath, pData->pPool);

		if (apr_strnatcmp(pInternalFile, pData->pchReqFile) == 0)
		{
			pData->pStatus = svn_wc_dup_status2(pStatus, pData->pPool);
		}
	}
}

CSvnFieldLoader::CSvnFieldLoader() :
	m_pFields(new CContentField*[4]),
	m_nFieldCount(0),
	m_pPool(svn_pool_create(NULL))
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

	try
	{
		const char* pchInternalPath = svn_path_internal_style(pchPath, pSubpool);
		const char* pchDir = svn_path_dirname(pchInternalPath, pSubpool);

		svn_opt_revision_t rev;
		rev.kind = svn_opt_revision_head;

		SvnFieldLoaderStatusBaton sBaton;
		sBaton.pchReqFile = pchInternalPath;
		sBaton.pStatus = NULL;
		sBaton.pPool = pSubpool;

		SVN_EX(svn_client_status2(NULL, pchDir, &rev, statusFunc, &sBaton, FALSE,
		                          TRUE, FALSE, TRUE, TRUE, m_pClientCtx, pSubpool));

		pRet = sBaton.pStatus;
	}
	catch (...)
	{
		svn_pool_destroy(pSubpool);
		throw;
	}

	if (pRet)
	{
		pRet = 	svn_wc_dup_status2(pRet, pPool);
	}

	svn_pool_destroy(pSubpool);
	return pRet;
}
