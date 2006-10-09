#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNCMTTIME__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNCMTTIME__

#include "ContentFieldSvn.h"

class CContentFieldSvnCmtTime : public CContentFieldSvn
{
public:
	CContentFieldSvnCmtTime(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnCmtTime();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
