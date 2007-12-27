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

#ifndef __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__ENTRYCACHE__
#define __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__ENTRYCACHE__

#include "SvnFieldLoader.h"

struct apr_pool_t;
struct apr_hash_t;
struct svn_wc_status2_t;
struct svn_wc_adm_access_t;

class CSvnFieldLoader::CEntryCache
{
public:
	CEntryCache(CSvnFieldLoader& oParent, const char* pchPath);
	~CEntryCache();

	const char* getPath() const;
	bool isPath(const char* pchPath) const;

	svn_wc_status2_t* getStatus(const char* pchEntryName);
	apr_hash_t* getProps(const char* pchEntryName);

	CEntryCache* switchPath(const char* pchNewPath);

private:
	class CStatusWalker; friend class CStatusWalker;

	CSvnPool m_oPool;
	CSvnFieldLoader& m_oParent;
	const char* m_pchPath;
	svn_wc_adm_access_t* m_pAdm;
	apr_hash_t* m_pStatuses;
	apr_hash_t* m_pProps;

	svn_wc_adm_access_t* getAdm();
	apr_hash_t* getStatuses();
	apr_hash_t* getProps();

	void openAdm();
	svn_wc_adm_access_t* openAdmFor(const char* pchPath, int iDepth, apr_pool_t* pPool);
	void collectStatuses();
	void collectProps();

	void makeExternalStatus(svn_wc_status2_t*& pStatus, const char* pchPath, apr_pool_t* pStatusPool, apr_pool_t* pTempPool);
};

#endif
