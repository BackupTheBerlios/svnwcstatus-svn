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
	class CEntryCache;

	CSvnFieldLoader();
	virtual ~CSvnFieldLoader();

	virtual CContentField& getFieldByIndex(int iIdx);
	virtual size_t getFieldCount() const;

	virtual void initParameters(const ContentDefaultParamStruct& sParams);

	svn_wc_status2_t* getStatusForPath(const char* pchPath, apr_pool_t* pPool);

	void aprTimeToFileTime(apr_time_t nTime, FILETIME& ftTime) const;

private:
	CSvnPool m_oPool;
	apr_array_header_t* m_pFields;
	svn_client_ctx_t* m_pClientCtx;

	CEntryCache* m_pLastEntry;

	CContentFieldSvn* getField(int iIdx);
	void appendField(CContentFieldSvn* pField);

	void createDefaultContentFields();
	void appendDefaultContentFields();

	static svn_wc_status2_t* dupEntry(svn_wc_status2_t* pEntry, apr_pool_t* pPool);
};

#endif
