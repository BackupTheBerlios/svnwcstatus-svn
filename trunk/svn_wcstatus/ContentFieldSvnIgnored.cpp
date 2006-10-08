#include "ContentFieldSvnIgnored.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceBoolean.h"

#include "SvnPool.h"

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
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceBoolean(*this, pchPath, pStatus->text_status == svn_wc_status_ignored);
}
