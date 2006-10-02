#include "ContentFieldSvnAuthor.h"
#include "FieldLoader.h"
#include "ContentInstanceString.h"

#include "svn_path.h"
#include "svn_client.h"

struct ContentFieldSvnAuthorStatusBaton
{
	const char* pchReqFile;
	svn_wc_status2_t* pStatus;
	apr_pool_t* pPool;
};

static void statusFunc(void* pBaton, const char* pchPath, svn_wc_status2_t *pStatus)
{
	ContentFieldSvnAuthorStatusBaton* pData = (ContentFieldSvnAuthorStatusBaton*) pBaton;

	if (!pData->pStatus)
	{
		const char* pInternalFile = svn_path_internal_style(pchPath, pData->pPool);

		if (apr_strnatcmp(pInternalFile, pData->pchReqFile) == 0)
		{
			pData->pStatus = svn_wc_dup_status2(pStatus, pData->pPool);
		}
	}
}

CContentFieldSvnAuthor::CContentFieldSvnAuthor()
{
}

CContentFieldSvnAuthor::~CContentFieldSvnAuthor()
{
}

const char* CContentFieldSvnAuthor::getName() const
{
	return "svn-author";
}

int CContentFieldSvnAuthor::getType() const
{
	return ft_string;
}

CContentInstancePtr CContentFieldSvnAuthor::getInstance(const char* pchFile)
{
	apr_pool_t* pPool;
	apr_status_t stat = apr_pool_create(&pPool, NULL);

	svn_client_ctx_t* pClientCtx;
	SVN_EX(svn_client_create_context(&pClientCtx, pPool));

	ContentFieldSvnAuthorStatusBaton sBaton;
	sBaton.pchReqFile = svn_path_internal_style(pchFile, pPool);
	sBaton.pPool = pPool;
	sBaton.pStatus = NULL;

	svn_opt_revision_t rev;
	rev.kind = svn_opt_revision_head;

	SVN_EX(svn_client_status2(NULL, svn_path_dirname(sBaton.pchReqFile, pPool),
		&rev, statusFunc, &sBaton, FALSE, TRUE, FALSE, FALSE, TRUE, pClientCtx, pPool));

	CContentInstancePtr pRes(NULL);

	if (sBaton.pStatus && sBaton.pStatus->entry)
		Reset(pRes, (CContentInstance*)new CContentInstanceString(*this, pchFile, sBaton.pStatus->entry->cmt_author));

	apr_pool_destroy(pPool);

	if (!pRes)
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);

	return pRes;
}
