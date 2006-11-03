#ifndef __TW_WDX_SVN_WCSTATUS__
#define __TW_WDX_SVN_WCSTATUS__

#include <windows.h>
#include <stdlib.h>

#include "contentplug.h"

#include "SvnEx.h"

#define SVN_EX(expr)                            \
{                                               \
	{svn_error_t* svn_err__temp = (expr);       \
	if (svn_err__temp)                          \
		throw new CSvnEx(svn_err__temp);}       \
}

#define PLUGIN_NAME "svn_wcstatus"

#ifdef _DEBUG
#define MODULE_NAME PLUGIN_NAME "D.wdx"
#else
#define MODULE_NAME PLUGIN_NAME ".wdx"
#endif

#define APR_ARRAY_GET(array, idx, type) \
	(*reinterpret_cast<type*>(array->elts + (array->elt_size * idx)));

#define APR_ARRAY_APPEND(array, value, type) \
	(*static_cast<type*>(apr_array_push(array)) = value);

#endif
