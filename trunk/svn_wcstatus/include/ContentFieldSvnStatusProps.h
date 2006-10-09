#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUSPROPS__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSTATUSPROPS__

#include "ContentFieldSvnStatus.h"

class CContentFieldSvnStatusProps : public CContentFieldSvnStatus
{
public:
	CContentFieldSvnStatusProps(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnStatusProps();

	virtual const char* getName() const;

protected:
	virtual int getStatusValue(svn_wc_status2_t* pStatus) const;
};

#endif
