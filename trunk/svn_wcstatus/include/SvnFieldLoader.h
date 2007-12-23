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

#ifndef __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__
#define __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__

#include "FieldLoader.h"

#include "SvnPool.h"

#include "apr_time.h"

class CContentFieldSvn;

struct apr_array_header_t;
struct svn_wc_status2_t;
struct svn_client_ctx_t;

class CSvnFieldLoader : public CFieldLoader
{
public:
	class CParameters;
	class CEntryCache; friend class CEntryCache;

	CSvnFieldLoader(const ContentDefaultParamStruct& sParams);
	virtual ~CSvnFieldLoader();

	virtual CContentField& getFieldByIndex(int iIdx);
	virtual size_t getFieldCount() const;

	svn_wc_status2_t* getStatusForPath(const char* pchPath, apr_pool_t* pPool);

	void aprTimeToFileTime(apr_time_t nTime, FILETIME& ftTime) const;

private:
	CSvnPool m_oPool;
	apr_array_header_t* m_pFields;
	svn_client_ctx_t* m_pClientCtx;

	CParameters* m_pParams;
	CEntryCache* m_pLastEntry;

	CEntryCache* getCacheForPath(const char* pchPath);

	CContentFieldSvn* getField(int iIdx);
	void appendField(CContentFieldSvn* pField);

	void emptyContentFields(int iInitialArrayLen);
	void appendDefaultContentFields();

	static svn_wc_status2_t* dupEntry(svn_wc_status2_t* pEntry, apr_pool_t* pPool);
};

#endif
