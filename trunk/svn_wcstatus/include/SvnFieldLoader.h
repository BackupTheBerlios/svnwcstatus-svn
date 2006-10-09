#ifndef __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__
#define __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__

#include "FieldLoader.h"

#include "SvnPool.h"

struct svn_wc_status2_t;
struct svn_client_ctx_t;

class CSvnFieldLoader : public CFieldLoader
{
public:
	class CEntryCache;

	CSvnFieldLoader();
	virtual ~CSvnFieldLoader();

	virtual CContentField& getFieldByIndex(int iIdx);

	svn_wc_status2_t* getStatusForPath(const char* pchPath, apr_pool_t* pPool);

	void aprTimeToFileTime(apr_time_t nTime, FILETIME& ftTime) const;

private:
	CContentField** m_pFields;
	size_t m_nFieldCount;
	CSvnPool m_oPool;
	svn_client_ctx_t* m_pClientCtx;

	CEntryCache* m_pLastEntry;

	static svn_wc_status2_t* dupEntry(svn_wc_status2_t* pEntry, apr_pool_t* pPool);
};

#endif
