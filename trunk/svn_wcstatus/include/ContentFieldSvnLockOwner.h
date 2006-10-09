#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNLOCKOWNER__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNLOCKOWNER__

#include "svn_wcstatus.h"

#include "ContentFieldSvn.h"

class CContentFieldSvnLockOwner : public CContentFieldSvn
{
public:
	CContentFieldSvnLockOwner(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnLockOwner();
	
	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
