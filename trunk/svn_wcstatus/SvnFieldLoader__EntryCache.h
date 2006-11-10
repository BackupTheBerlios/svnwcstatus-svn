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

	CEntryCache* switchPath(const char* pchNewPath);

private:
	class CStatusWalker; friend class CStatusWalker;

	CSvnPool m_oPool;
	CSvnFieldLoader& m_oParent;
	const char* m_pchPath;
	svn_wc_adm_access_t* m_pAdm;
	apr_hash_t* m_pStatuses;

	svn_wc_adm_access_t* getAdm();
	apr_hash_t* getStatuses();

	void openAdm();
	svn_wc_adm_access_t* openAdmFor(const char* pchPath, int iDepth, apr_pool_t* pPool);
	void collectStatuses();

	void makeExternalStatus(svn_wc_status2_t*& pStatus, const char* pchPath, apr_pool_t* pStatusPool, apr_pool_t* pTempPool);
};

#endif
