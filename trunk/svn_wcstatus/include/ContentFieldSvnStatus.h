#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUS__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUS__

#include "ContentFieldSvnMultiChoice.h"

class CContentFieldSvnStatus : public CContentFieldSvnMultiChoice
{
public:
	CContentFieldSvnStatus(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnStatus();

	virtual const char* getName() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
