#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNLOCKCREATIONDATE__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNLOCKCREATIONDATE__

#include "ContentFieldSvn.h"

class CContentFieldSvnLockCreationDate : public CContentFieldSvn
{
public:
	CContentFieldSvnLockCreationDate(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnLockCreationDate();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
