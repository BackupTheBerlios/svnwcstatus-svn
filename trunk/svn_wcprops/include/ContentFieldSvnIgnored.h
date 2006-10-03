#ifndef __TW_WDX_SVN_WCPROPS_CONTENTFIELDSVNIGNORED__
#define __TW_WDX_SVN_WCPROPS_CONTENTFIELDSVNIGNORED__

#include "svn_wcprops.h"

#include "ContentFieldSvn.h"

class CContentFieldSvnIgnored : public CContentFieldSvn
{
public:
	CContentFieldSvnIgnored(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnIgnored();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstancePtr getInstance(const char* pchPath);
};

#endif
