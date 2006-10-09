#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNABSENT__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNABSENT__

#include "ContentFieldSvn.h"

class CContentFieldSvnAbsent : public CContentFieldSvn
{
public:
	CContentFieldSvnAbsent(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnAbsent();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
