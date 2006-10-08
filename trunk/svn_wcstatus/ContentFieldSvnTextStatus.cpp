#include "ContentFieldSvnTextStatus.h"
#include "SvnFieldLoader.h"
#include "MultiChoiceDefStatus.h"
#include "ContentInstanceMultiChoice.h"

#include "SvnPool.h"

#include "svn_wc.h"

#pragma warning(disable: 4355)  // 'this' : used in base member initializer list
CContentFieldSvnTextStatus::CContentFieldSvnTextStatus(CSvnFieldLoader& oLoader) :
	CContentFieldSvnMultiChoice(oLoader, new CMultiChoiceDefStatus(*this))
{
}
#pragma warning(default: 4355)

CContentFieldSvnTextStatus::~CContentFieldSvnTextStatus()
{
}

const char* CContentFieldSvnTextStatus::getName() const
{
	return "svn-text-status";
}

CContentInstancePtr CContentFieldSvnTextStatus::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	return new CContentInstanceMultiChoice(*getMultiChoiceDef(), pchPath, pStatus ? pStatus->text_status : CMultiChoiceDef::eMultiChoiceEmpty);
}
