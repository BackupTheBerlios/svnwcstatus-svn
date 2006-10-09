#include "ContentFieldSvnStatusProps.h"
#include "MultiChoiceDef.h"

#include "svn_wc.h"

CContentFieldSvnStatusProps::CContentFieldSvnStatusProps(CSvnFieldLoader& oLoader) :
	CContentFieldSvnStatus(oLoader)
{
}

CContentFieldSvnStatusProps::~CContentFieldSvnStatusProps()
{
}

const char* CContentFieldSvnStatusProps::getName() const
{
	return "svn-props-status";
}

int CContentFieldSvnStatusProps::getStatusValue(svn_wc_status2_t* pStatus) const
{
	return (pStatus && pStatus->entry)? pStatus->prop_status : CMultiChoiceDef::eMultiChoiceEmpty;
}
