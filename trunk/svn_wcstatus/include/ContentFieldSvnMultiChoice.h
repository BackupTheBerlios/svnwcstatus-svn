#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNMULTICHOICE__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNMULTICHOICE__

#include "ContentFieldSvn.h"

class CContentFieldSvnMultiChoice : public CContentFieldSvn
{
public:
	CContentFieldSvnMultiChoice(CSvnFieldLoader& oLoader, CMultiChoiceDef* pDef);
	virtual ~CContentFieldSvnMultiChoice();

	virtual int getType() const;

	const CMultiChoiceDef* getMultiChoiceDef() const;

private:
	CMultiChoiceDef* m_pDef;
};

#endif
