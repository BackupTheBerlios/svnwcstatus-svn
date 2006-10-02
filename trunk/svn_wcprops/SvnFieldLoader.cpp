#include "SvnFieldLoader.h"
#include "ContentFieldSvnAuthor.h"

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
	SvnFieldLoaderStatusBaton* pData = (SvnFieldLoaderStatusBaton*) pBaton;

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
	m_pFields(new CContentField*[2]),
	m_nFieldCount(0)
{
	m_pFields[m_nFieldCount++] = new CContentFieldSvnAuthor(*this);
	m_pFields[m_nFieldCount] = NULL;
}

CSvnFieldLoader::~CSvnFieldLoader()
{
	for (CContentField* pField = *m_pFields; pField; ++pField)
	{
		delete pField;
	}

	delete [] m_pFields;
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
	apr_pool_t* pSubpool = svn_pool_create(pPool);
	svn_client_ctx_t* pClientCtx;

	svn_opt_revision_t rev;
	rev.kind = svn_opt_revision_head;

	SvnFieldLoaderStatusBaton sBaton;
	sBaton.pchReqFile = svn_path_internal_style(pchPath, pSubpool);
	sBaton.pPool = pPool;
	sBaton.pStatus = NULL;

	try
	{
		SVN_EX(svn_client_create_context(&pClientCtx, pSubpool));
		SVN_EX(svn_client_status2(NULL, svn_path_dirname(sBaton.pchReqFile, pSubpool),
			&rev, statusFunc, &sBaton, FALSE, TRUE, FALSE, FALSE, TRUE, pClientCtx, pSubpool));
	}
	catch (...)
	{
		svn_pool_destroy(pSubpool);
		throw;
	}

	svn_pool_destroy(pSubpool);
	return sBaton.pStatus;
}
