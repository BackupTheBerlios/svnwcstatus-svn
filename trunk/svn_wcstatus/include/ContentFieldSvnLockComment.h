#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNLOCKCOMMENT__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNLOCKCOMMENT__

#include "svn_wcstatus.h"

#include "ContentFieldSvn.h"

class CContentFieldSvnLockComment : public CContentFieldSvn
{
public:
	CContentFieldSvnLockComment(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnLockComment();
	
	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
