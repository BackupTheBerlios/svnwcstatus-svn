#ifndef __TW_WDX_SVN_WCPROPS__
#define __TW_WDX_SVN_WCPROPS__

#include <windows.h>
#include <stdlib.h>

#include "contentplug.h"

#include "SmartPtr.h"

#include "SvnEx.h"

#define SVN_EX(expr)                            \
{                                               \
	{svn_error_t* svn_err__temp = (expr);       \
	if (svn_err__temp)                          \
		throw new CSvnEx(svn_err__temp);}       \
}

#endif
