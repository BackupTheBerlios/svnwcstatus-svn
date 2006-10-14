#ifndef __TW_WDX_SVN_WCSTATUS_SVNEX__
#define __TW_WDX_SVN_WCSTATUS_SVNEX__

struct svn_error_t;

class CSvnEx
{
public:
	CSvnEx(svn_error_t* pErr);
	virtual ~CSvnEx();

private:
	svn_error_t* m_pErr;
};

#endif
