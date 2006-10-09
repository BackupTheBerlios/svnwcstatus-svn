#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUS__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUS__

#include "ContentFieldSvnMultiChoice.h"

struct svn_wc_status2_t;

class CContentFieldSvnStatus : public CContentFieldSvnMultiChoice
{
public:
	CContentFieldSvnStatus(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnStatus();

	virtual CContentInstance* getInstance(const char* pchPath);

protected:
	virtual int getStatusValue(svn_wc_status2_t* pStatus) const = 0;
};

#endif
