#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNCMTREV__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNCMTREV__

#include "ContentFieldSvn.h"

class CContentFieldSvnCmtRev : public CContentFieldSvn
{
public:
	CContentFieldSvnCmtRev(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnCmtRev();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
