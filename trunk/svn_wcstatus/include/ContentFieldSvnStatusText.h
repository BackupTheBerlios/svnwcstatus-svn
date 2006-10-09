#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUSTEXT__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUSTEXT__

#include "ContentFieldSvnStatus.h"

class CContentFieldSvnStatusText : public CContentFieldSvnStatus
{
public:
	CContentFieldSvnStatusText(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnStatusText();

	virtual const char* getName() const;

protected:
	virtual int getStatusValue(svn_wc_status2_t* pStatus) const;
};

#endif
