#include "ContentFieldSvnCopied.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceBoolean.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnCopied::CContentFieldSvnCopied(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnCopied::~CContentFieldSvnCopied()
{
}

const char* CContentFieldSvnCopied::getName() const
{
	return "svn-copied";
}

int CContentFieldSvnCopied::getType() const
{
	return ft_boolean;
}

CContentInstance* CContentFieldSvnCopied::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceBoolean(*this, pchPath, pStatus->entry->copied == TRUE);
}
