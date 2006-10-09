#include "ContentFieldSvnCmtTime.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceDateTime.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnCmtTime::CContentFieldSvnCmtTime(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnCmtTime::~CContentFieldSvnCmtTime()
{
}

const char* CContentFieldSvnCmtTime::getName() const
{
	return "svn-cmt-time";
}

int CContentFieldSvnCmtTime::getType() const
{
	return ft_datetime;
}

CContentInstance* CContentFieldSvnCmtTime::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	FILETIME ftTime;
	getParent().aprTimeToFileTime(pStatus->entry->cmt_date, ftTime);

	return new CContentInstanceDateTime(*this, pchPath, ftTime);
}
