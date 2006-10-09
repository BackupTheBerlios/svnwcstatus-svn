#include "ContentFieldSvnTextTime.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceDateTime.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnTextTime::CContentFieldSvnTextTime(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnTextTime::~CContentFieldSvnTextTime()
{
}

const char* CContentFieldSvnTextTime::getName() const
{
	return "svn-text-time";
}

int CContentFieldSvnTextTime::getType() const
{
	return ft_datetime;
}

CContentInstance* CContentFieldSvnTextTime::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	if (pStatus->entry && pStatus->entry->text_time != 0)
	{
		FILETIME ftTime;
		getParent().aprTimeToFileTime(pStatus->entry->text_time, ftTime);
		return new CContentInstanceDateTime(*this, pchPath, ftTime);
	}

	return new CContentInstanceEmpty(*this, pchPath);
}
