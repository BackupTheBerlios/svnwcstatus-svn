#ifndef __TW_WDX_SVN_WCPROPS_SVNPOOL__
#define __TW_WDX_SVN_WCPROPS_SVNPOOL__

struct apr_pool_t;

class CSvnPool
{
public:
	CSvnPool();
	explicit CSvnPool(CSvnPool& oParent);
	explicit CSvnPool(apr_pool_t* pParent);
	~CSvnPool();

	CSvnPool& clear();
	void destroy();

	void release();

	operator apr_pool_t*();

private:
	apr_pool_t* m_pPool;
};

#endif
