#include "ContentFieldSvnSchedule.h"
#include "SvnFieldLoader.h"
#include "MultiChoiceDefSchedule.h"
#include "ContentInstanceMultiChoice.h"

#include "SvnPool.h"

#include "svn_wc.h"

#pragma warning(disable: 4355)  // 'this' : used in base member initializer list
CContentFieldSvnSchedule::CContentFieldSvnSchedule(CSvnFieldLoader& oLoader) :
	CContentFieldSvnMultiChoice(oLoader, new CMultiChoiceDefSchedule(*this))
{
}
#pragma warning(default: 4355)

CContentFieldSvnSchedule::~CContentFieldSvnSchedule()
{
}

const char* CContentFieldSvnSchedule::getName() const
{
	return "svn-schedule";
}

CContentInstancePtr CContentFieldSvnSchedule::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	return new CContentInstanceMultiChoice(*getMultiChoiceDef(), pchPath, pStatus && pStatus->entry ? pStatus->entry->schedule + 1 : CMultiChoiceDef::eMultiChoiceEmpty);
}
