#include "ContentFieldSvnIncomplete.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceBoolean.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnIncomplete::CContentFieldSvnIncomplete(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnIncomplete::~CContentFieldSvnIncomplete()
{
}

const char* CContentFieldSvnIncomplete::getName() const
{
	return "svn-incomplete";
}

int CContentFieldSvnIncomplete::getType() const
{
	return ft_boolean;
}

CContentInstance* CContentFieldSvnIncomplete::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceBoolean(*this, pchPath, pStatus->entry->incomplete == TRUE);
}
