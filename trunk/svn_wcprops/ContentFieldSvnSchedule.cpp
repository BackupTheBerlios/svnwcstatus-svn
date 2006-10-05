#include "ContentFieldSvnSchedule.h"
#include "SvnFieldLoader.h"
#include "MultiChoiceDefSchedule.h"
#include "ContentInstanceMultiChoice.h"

#include "svn_pools.h"
#include "svn_path.h"
#include "svn_client.h"

#pragma warning(disable: 4355)  // 'this' : used in base member initializer list
CContentFieldSvnSchedule::CContentFieldSvnSchedule(CSvnFieldLoader& oLoader) :
	CContentFieldSvn(oLoader),
	m_pDef(new CMultiChoiceDefSchedule(*this))
{
}
#pragma warning(default: 4355)

CContentFieldSvnSchedule::~CContentFieldSvnSchedule()
{
	delete m_pDef;
}

const char* CContentFieldSvnSchedule::getName() const
{
	return "svn-schedule";
}

int CContentFieldSvnSchedule::getType() const
{
	return ft_multiplechoice;
}

const CMultiChoiceDef* CContentFieldSvnSchedule::getMultiChoiceDef() const
{
	return m_pDef;
}

CContentInstancePtr CContentFieldSvnSchedule::getInstance(const char* pchPath)
{
	CSvnPool oPool;
	svn_wc_status2_t* pStatus = getParent().getStatusForPath(pchPath, oPool);

	return new CContentInstanceMultiChoice(*m_pDef, pchPath, pStatus && pStatus->entry ? pStatus->entry->schedule + 1 : CMultiChoiceDef::eMultiChoiceEmpty);
}
