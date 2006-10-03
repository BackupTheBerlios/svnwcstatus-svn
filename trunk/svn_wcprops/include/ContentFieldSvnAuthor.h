#ifndef __TW_WDX_SVN_WCPROPS_CONTENTFIELDSVNAUTHOR__
#define __TW_WDX_SVN_WCPROPS_CONTENTFIELDSVNAUTHOR__

#include "svn_wcprops.h"

#include "ContentFieldSvn.h"

class CContentFieldSvnAuthor : public CContentFieldSvn
{
public:
	CContentFieldSvnAuthor(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnAuthor();
	
	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstancePtr getInstance(const char* pchPath);
};

#endif
