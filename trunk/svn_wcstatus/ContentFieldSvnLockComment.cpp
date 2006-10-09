#include "ContentFieldSvnLockComment.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceEmpty.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnLockComment::CContentFieldSvnLockComment(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnLockComment::~CContentFieldSvnLockComment()
{
}

const char* CContentFieldSvnLockComment::getName() const
{
	return "svn-lock-comment";
}

int CContentFieldSvnLockComment::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnLockComment::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return pStatus->entry && pStatus->entry->lock_comment ? 
		static_cast<CContentInstance*>(new CContentInstanceString(*this, pchPath, pStatus->entry->lock_comment)) :
		static_cast<CContentInstance*>(new CContentInstanceEmpty(*this, pchPath));
}
