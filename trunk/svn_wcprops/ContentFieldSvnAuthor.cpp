#include "ContentFieldSvnAuthor.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceString.h"

#include "svn_pools.h"
#include "svn_path.h"
#include "svn_client.h"

CContentFieldSvnAuthor::CContentFieldSvnAuthor(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
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

CContentInstancePtr CContentFieldSvnAuthor::getInstance(const char* pchPath)
{
	apr_pool_t* pPool = svn_pool_create(NULL);

	svn_wc_status2_t* pStatus = NULL;

	try
	{
		pStatus = getParent().getStatusForPath(pchPath, pPool);
	}
	catch (...)
	{
		svn_pool_destroy(pPool);
		throw;
	}

	CContentInstancePtr pRes(NULL);

	if (pStatus && pStatus->entry)
		Reset(pRes, (CContentInstance*) new CContentInstanceString(*this, pchPath, pStatus->entry->cmt_author));

	svn_pool_destroy(pPool);

	if (!pRes)
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);

	return pRes;
}
