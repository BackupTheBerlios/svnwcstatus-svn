#include "ContentFieldSvnRevision.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceNumeric32.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnRevision::CContentFieldSvnRevision(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnRevision::~CContentFieldSvnRevision()
{
}

const char* CContentFieldSvnRevision::getName() const
{
	return "svn-revision";
}

int CContentFieldSvnRevision::getType() const
{
	return ft_numeric_32;
}

CContentInstance* CContentFieldSvnRevision::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceNumeric32(*this, pchPath, pStatus->entry->revision);
}
