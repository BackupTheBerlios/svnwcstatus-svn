#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVN__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVN__

#include "ContentField.h"

class CSvnFieldLoader;

class CContentFieldSvn : public CContentField
{
public:
	CContentFieldSvn(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvn();

protected:
	CSvnFieldLoader& getParent();

private:
	CSvnFieldLoader& m_oLoader;
};

#endif
