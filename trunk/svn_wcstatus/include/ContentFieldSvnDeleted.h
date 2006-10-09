#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNDELETED__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNDELETED__

#include "ContentFieldSvn.h"

class CContentFieldSvnDeleted : public CContentFieldSvn
{
public:
	CContentFieldSvnDeleted(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnDeleted();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
