#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNIGNORED__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNIGNORED__

#include "svn_wcstatus.h"

#include "ContentFieldSvn.h"

class CContentFieldSvnIgnored : public CContentFieldSvn
{
public:
	CContentFieldSvnIgnored(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnIgnored();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
