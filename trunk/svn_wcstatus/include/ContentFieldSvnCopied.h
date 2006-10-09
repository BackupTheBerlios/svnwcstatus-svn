#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNCOPIED__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNCOPIED__

#include "ContentFieldSvn.h"

class CContentFieldSvnCopied : public CContentFieldSvn
{
public:
	CContentFieldSvnCopied(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnCopied();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
