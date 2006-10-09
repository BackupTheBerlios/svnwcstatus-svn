#include "ContentFieldSvnPropTime.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceDateTime.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnPropTime::CContentFieldSvnPropTime(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnPropTime::~CContentFieldSvnPropTime()
{
}

const char* CContentFieldSvnPropTime::getName() const
{
	return "svn-prop-time";
}

int CContentFieldSvnPropTime::getType() const
{
	return ft_datetime;
}

CContentInstance* CContentFieldSvnPropTime::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	if (pStatus->entry && pStatus->entry->prop_time != 0)
	{
		FILETIME ftTime;
		getParent().aprTimeToFileTime(pStatus->entry->prop_time, ftTime);
		return new CContentInstanceDateTime(*this, pchPath, ftTime);
	}

	return new CContentInstanceEmpty(*this, pchPath);
}
