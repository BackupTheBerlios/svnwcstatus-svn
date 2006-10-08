#ifndef __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__ENTRYCACHE__
#define __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__ENTRYCACHE__

#include "SvnFieldLoader.h"

struct apr_pool_t;
struct svn_wc_status2_t;

class CSvnFieldLoader::CEntryCache
{
public:
	CEntryCache(const char* pchPath);
	~CEntryCache();

	static CEntryCache* pcreate(apr_pool_t* pPool, const char* pchPath);

	const char* getPath() const;
	bool isPath(const char* pchPath) const;
	svn_wc_status2_t* getEntry(const char* pchEntryName) const;

	void putEntry(svn_wc_status2_t* pEntry, const char* pchName);

	void clear(const char* pchNewPath);

private:
	CEntryCache(apr_pool_t* pParent, const char* pchPath);

	apr_pool_t* m_pPool;
	const char* m_pchPath;
	apr_hash_t* m_pEntries;
};

#endif
