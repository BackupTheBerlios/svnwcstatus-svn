#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNTEXTSTATUS__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNTEXTSTATUS__

#include "ContentFieldSvnStatus.h"

class CContentFieldSvnTextStatus : public CContentFieldSvnStatus
{
public:
	CContentFieldSvnTextStatus(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnTextStatus();

	virtual const char* getName() const;

protected:
	virtual int getStatusValue(svn_wc_status2_t* pStatus) const;
};

#endif
