#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNREPOS__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNREPOS__

#include "ContentFieldSvn.h"

class CContentFieldSvnRepos : public CContentFieldSvn
{
public:
	CContentFieldSvnRepos(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnRepos();

	virtual const char* getName() const;
	virtual int getType() const;

	virtual CContentInstance* getInstance(const char* pchPath);
};

#endif
