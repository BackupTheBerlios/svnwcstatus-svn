#ifndef __TW_WDX_SVN_WCPROPS_SVNFIELDLOADER__
#define __TW_WDX_SVN_WCPROPS_SVNFIELDLOADER__

#include "FieldLoader.h"

struct svn_wc_status2_t;
struct svn_client_ctx_t;

class CSvnFieldLoader : public CFieldLoader
{
public:
	CSvnFieldLoader();
	virtual ~CSvnFieldLoader();

	virtual CContentField& getFieldByIndex(int iIdx);

	svn_wc_status2_t* getStatusForPath(const char* pchPath, apr_pool_t* pPool);

private:
	CContentField** m_pFields;
	size_t m_nFieldCount;
	apr_pool_t* m_pPool;
	svn_client_ctx_t* m_pClientCtx;
};

#endif
