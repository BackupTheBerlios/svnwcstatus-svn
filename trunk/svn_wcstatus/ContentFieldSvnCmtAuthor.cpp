#include "ContentFieldSvnCmtAuthor.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnCmtAuthor::CContentFieldSvnCmtAuthor(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnCmtAuthor::~CContentFieldSvnCmtAuthor()
{
}

const char* CContentFieldSvnCmtAuthor::getName() const
{
	return "svn-cmt-author";
}

int CContentFieldSvnCmtAuthor::getType() const
{
	return ft_string;
}

CContentInstance* CContentFieldSvnCmtAuthor::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceString(*this, pchPath, pStatus->entry->cmt_author);
}
