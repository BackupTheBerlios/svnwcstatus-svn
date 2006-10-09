#include "ContentFieldSvnTextStatus.h"
#include "MultiChoiceDef.h"

#include "svn_wc.h"

CContentFieldSvnTextStatus::CContentFieldSvnTextStatus(CSvnFieldLoader& oLoader) :
	CContentFieldSvnStatus(oLoader)
{
}

CContentFieldSvnTextStatus::~CContentFieldSvnTextStatus()
{
}

const char* CContentFieldSvnTextStatus::getName() const
{
	return "svn-text-status";
}

int CContentFieldSvnTextStatus::getStatusValue(svn_wc_status2_t* pStatus) const
{
	return pStatus ? pStatus->text_status : CMultiChoiceDef::eMultiChoiceEmpty;
}
