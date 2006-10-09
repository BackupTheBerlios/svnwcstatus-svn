#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNLOCKTOKEN__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNLOCKTOKEN__

#include "svn_wcstatus.h"

#include "ContentFieldSvn.h"

class CContentFieldSvnLockToken : public CContentFieldSvn
{
public:
	CContentFieldSvnLockToken(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnLockToken();
	
	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
