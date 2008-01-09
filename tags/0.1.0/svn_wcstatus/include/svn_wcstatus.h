/* Copyright 2007, 2008 Tom Wieczorek
 *
 * This file is part of svn_wcstatus.
 *
 * svn_wcstatus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * svn_wcstatus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with svn_wcstatus. If not, see <http://www.gnu.org/licenses/>.
 */

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
