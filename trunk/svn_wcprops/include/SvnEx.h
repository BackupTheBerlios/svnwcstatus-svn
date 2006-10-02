#ifndef __TW_WDX_SVN_WCPROPS_SVNEX__
#define __TW_WDX_SVN_WCPROPS_SVNEX__

#include "svn_error.h"

class CSvnEx
{
public:
	CSvnEx(svn_error_t* pErr);
	virtual ~CSvnEx();

};

#endif
