#include "ContentFieldSvnLockCreationDate.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceDateTime.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnLockCreationDate::CContentFieldSvnLockCreationDate(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnLockCreationDate::~CContentFieldSvnLockCreationDate()
{
}

const char* CContentFieldSvnLockCreationDate::getName() const
{
	return "svn-lock-creation-date";
}

int CContentFieldSvnLockCreationDate::getType() const
{
	return ft_datetime;
}

CContentInstance* CContentFieldSvnLockCreationDate::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	if (pStatus->entry && pStatus->entry->lock_creation_date != 0)
	{
		FILETIME ftTime;
		getParent().aprTimeToFileTime(pStatus->entry->lock_creation_date, ftTime);
		return new CContentInstanceDateTime(*this, pchPath, ftTime);
	}

	return new CContentInstanceEmpty(*this, pchPath);
}
