#include "ContentFieldSvnMultiChoice.h"
#include "MultiChoiceDef.h"

CContentFieldSvnMultiChoice::CContentFieldSvnMultiChoice(CSvnFieldLoader& oLoader, CMultiChoiceDef* pDef) :
	CContentFieldSvn(oLoader),
	m_pDef(pDef)
{
}

CContentFieldSvnMultiChoice::~CContentFieldSvnMultiChoice()
{
	delete m_pDef;
}

int CContentFieldSvnMultiChoice::getType() const
{
	return ft_multiplechoice;
}

const CMultiChoiceDef* CContentFieldSvnMultiChoice::getMultiChoiceDef() const
{
	return m_pDef;
}
