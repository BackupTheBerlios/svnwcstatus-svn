#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNCMTAUTHOR__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNCMTAUTHOR__

#include "svn_wcstatus.h"

#include "ContentFieldSvn.h"

class CContentFieldSvnCmtAuthor : public CContentFieldSvn
{
public:
	CContentFieldSvnCmtAuthor(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnCmtAuthor();
	
	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
