#include "ContentFieldSvnUuid.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnUuid::CContentFieldSvnUuid(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnUuid::~CContentFieldSvnUuid()
{
}

const char* CContentFieldSvnUuid::getName() const
{
	return "svn-uuid";
}

int CContentFieldSvnUuid::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnUuid::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceString(*this, pchPath, pStatus->entry->uuid);
}
