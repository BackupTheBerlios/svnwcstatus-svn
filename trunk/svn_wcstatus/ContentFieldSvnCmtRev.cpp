#include "ContentFieldSvnCmtRev.h"
#include "SvnFieldLoader.h"
#include "ContentInstanceNumeric32.h"

#include "SvnPool.h"

#include "svn_wc.h"

CContentFieldSvnCmtRev::CContentFieldSvnCmtRev(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader)
{
}

CContentFieldSvnCmtRev::~CContentFieldSvnCmtRev()
{
}

const char* CContentFieldSvnCmtRev::getName() const
{
	return "svn-cmt-rev";
}

int CContentFieldSvnCmtRev::getType() const
{
	return ft_numeric_32;
}

CContentInstance* CContentFieldSvnCmtRev::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	if (!pStatus || !pStatus->entry)
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchField);
	}

	return new CContentInstanceNumeric32(*this, pchPath, pStatus->entry->cmt_rev);
}
