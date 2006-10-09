#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNUUID__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNUUID__

#include "ContentFieldSvn.h"

class CContentFieldSvnUuid : public CContentFieldSvn
{
public:
	CContentFieldSvnUuid(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnUuid();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
