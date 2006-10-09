#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNINCOMPLETE__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNINCOMPLETE__

#include "ContentFieldSvn.h"

class CContentFieldSvnIncomplete : public CContentFieldSvn
{
public:
	CContentFieldSvnIncomplete(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnIncomplete();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
