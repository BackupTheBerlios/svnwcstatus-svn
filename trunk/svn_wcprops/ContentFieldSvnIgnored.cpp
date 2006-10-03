#include "ContentFieldSvnIgnored.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceBoolean.h"

#include "svn_pools.h"
#include "svn_wc.h"

CContentFieldSvnIgnored::CContentFieldSvnIgnored(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnIgnored::~CContentFieldSvnIgnored()
{
}

const char* CContentFieldSvnIgnored::getName() const
{
	return "svn-ignored";
}

int CContentFieldSvnIgnored::getType() const
{
	return ft_boolean;
}

CContentInstancePtr CContentFieldSvnIgnored::getInstance(const char* pchPath)
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

	if (pStatus)
		Reset(pRes, (CContentInstance*) new CContentInstanceBoolean(*this, pchPath, pStatus->text_status == svn_wc_status_ignored));

	svn_pool_destroy(pPool);

	if (!pRes)
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);

	return pRes;
}
