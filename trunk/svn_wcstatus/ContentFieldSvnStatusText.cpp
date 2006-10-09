#include "ContentFieldSvnStatusText.h"
#include "MultiChoiceDef.h"

#include "svn_wc.h"

CContentFieldSvnStatusText::CContentFieldSvnStatusText(CSvnFieldLoader& oLoader) :
	CContentFieldSvnStatus(oLoader)
{
}

CContentFieldSvnStatusText::~CContentFieldSvnStatusText()
{
}

const char* CContentFieldSvnStatusText::getName() const
{
	return "svn-text-status";
}

int CContentFieldSvnStatusText::getStatusValue(svn_wc_status2_t* pStatus) const
{
	return pStatus ? pStatus->text_status : CMultiChoiceDef::eMultiChoiceEmpty;
}
