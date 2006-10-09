#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNURL__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNURL__

#include "ContentFieldSvn.h"

class CContentFieldSvnUrl : public CContentFieldSvn
{
public:
	CContentFieldSvnUrl(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnUrl();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
