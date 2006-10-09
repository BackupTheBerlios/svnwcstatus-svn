#include "ContentFieldSvnLockToken.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnLockToken::CContentFieldSvnLockToken(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnLockToken::~CContentFieldSvnLockToken()
{
}

const char* CContentFieldSvnLockToken::getName() const
{
	return "svn-lock-token";
}

int CContentFieldSvnLockToken::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnLockToken::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return pStatus->entry && pStatus->entry->lock_token ? 
		static_cast<CContentInstance*>(new CContentInstanceString(*this, pchPath, pStatus->entry->lock_token)) :
		static_cast<CContentInstance*>(new CContentInstanceEmpty(*this, pchPath));
}
