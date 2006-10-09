#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNREVISION__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNREVISION__

#include "ContentFieldSvn.h"

class CContentFieldSvnRevision : public CContentFieldSvn
{
public:
	CContentFieldSvnRevision(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnRevision();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
