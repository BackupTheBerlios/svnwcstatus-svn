#ifndef __TW_WDX_SVN_WCSTATUS_SVNPOOL__
#define __TW_WDX_SVN_WCSTATUS_SVNPOOL__

struct apr_pool_t;

class CSvnPool
{
public:
	CSvnPool();
	explicit CSvnPool(CSvnPool& oParent);
	explicit CSvnPool(apr_pool_t* pParent);
	~CSvnPool();

	apr_pool_t* replace(apr_pool_t* pPool);

	CSvnPool& clear();
	void destroy();

	apr_pool_t* release();

	operator apr_pool_t*();

private:
	apr_pool_t* m_pPool;
};

#endif
