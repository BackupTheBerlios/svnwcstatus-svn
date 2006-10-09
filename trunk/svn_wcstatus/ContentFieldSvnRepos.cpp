#include "ContentFieldSvnRepos.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnRepos::CContentFieldSvnRepos(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnRepos::~CContentFieldSvnRepos()
{
}

const char* CContentFieldSvnRepos::getName() const
{
	return "svn-repos";
}

int CContentFieldSvnRepos::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnRepos::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceString(*this, pchPath, pStatus->entry->repos);
}
