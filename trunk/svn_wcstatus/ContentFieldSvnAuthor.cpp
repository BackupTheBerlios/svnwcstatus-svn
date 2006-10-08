#include "ContentFieldSvnAuthor.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceString.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnAuthor::CContentFieldSvnAuthor(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnAuthor::~CContentFieldSvnAuthor()
{
}

const char* CContentFieldSvnAuthor::getName() const
{
	return "svn-author";
}

int CContentFieldSvnAuthor::getType() const
{
	return ft_string;
}

CContentInstancePtr CContentFieldSvnAuthor::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceString(*this, pchPath, pStatus->entry->cmt_author);
}
