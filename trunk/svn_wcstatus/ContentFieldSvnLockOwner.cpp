#include "ContentFieldSvnLockOwner.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnLockOwner::CContentFieldSvnLockOwner(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnLockOwner::~CContentFieldSvnLockOwner()
{
}

const char* CContentFieldSvnLockOwner::getName() const
{
	return "svn-lock-owner";
}

int CContentFieldSvnLockOwner::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnLockOwner::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return pStatus->entry && pStatus->entry->lock_owner ? 
		static_cast<CContentInstance*>(new CContentInstanceString(*this, pchPath, pStatus->entry->lock_owner)) :
		static_cast<CContentInstance*>(new CContentInstanceEmpty(*this, pchPath));
}
