#include "ContentFieldSvnUrl.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnUrl::CContentFieldSvnUrl(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnUrl::~CContentFieldSvnUrl()
{
}

const char* CContentFieldSvnUrl::getName() const
{
	return "svn-url";
}

int CContentFieldSvnUrl::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnUrl::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceString(*this, pchPath, pStatus->entry->url);
}
