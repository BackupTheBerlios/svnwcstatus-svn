#include "ContentFieldSvnAbsent.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceBoolean.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnAbsent::CContentFieldSvnAbsent(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnAbsent::~CContentFieldSvnAbsent()
{
}

const char* CContentFieldSvnAbsent::getName() const
{
	return "svn-absent";
}

int CContentFieldSvnAbsent::getType() const
{
	return ft_boolean;
}

CContentInstance* CContentFieldSvnAbsent::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceBoolean(*this, pchPath, pStatus->entry->absent == TRUE);
}
