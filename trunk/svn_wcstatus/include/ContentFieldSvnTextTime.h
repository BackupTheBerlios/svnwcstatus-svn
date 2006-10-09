#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNTEXTTIME__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNTEXTTIME__

#include "ContentFieldSvn.h"

class CContentFieldSvnTextTime : public CContentFieldSvn
{
public:
	CContentFieldSvnTextTime(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnTextTime();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
