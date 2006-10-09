#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNPROPTIME__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNPROPTIME__

#include "ContentFieldSvn.h"

class CContentFieldSvnPropTime : public CContentFieldSvn
{
public:
	CContentFieldSvnPropTime(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnPropTime();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
