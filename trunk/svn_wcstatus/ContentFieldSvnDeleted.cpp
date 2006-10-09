#include "ContentFieldSvnDeleted.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceBoolean.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnDeleted::CContentFieldSvnDeleted(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnDeleted::~CContentFieldSvnDeleted()
{
}

const char* CContentFieldSvnDeleted::getName() const
{
	return "svn-deleted";
}

int CContentFieldSvnDeleted::getType() const
{
	return ft_boolean;
}

CContentInstance* CContentFieldSvnDeleted::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceBoolean(*this, pchPath, pStatus->entry->copied == TRUE);
}
