#include "ContentFieldSvn.h"

CContentFieldSvn::CContentFieldSvn(CSvnFieldLoader& oLoader) :
	m_oLoader(oLoader)
{
}

CContentFieldSvn::~CContentFieldSvn()
{
}

CSvnFieldLoader& CContentFieldSvn::getParent()
{
	return m_oLoader;
}
