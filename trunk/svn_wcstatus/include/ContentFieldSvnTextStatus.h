#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUS__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUS__

#include "ContentFieldSvnMultiChoice.h"

class CContentFieldSvnTextStatus : public CContentFieldSvnMultiChoice
{
public:
	CContentFieldSvnTextStatus(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnTextStatus();

	virtual const char* getName() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
