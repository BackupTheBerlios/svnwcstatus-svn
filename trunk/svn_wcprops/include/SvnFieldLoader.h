#ifndef __TW_WDX_SVN_WCPROPS_SVNFIELDLOADER__
#define __TW_WDX_SVN_WCPROPS_SVNFIELDLOADER__

#include "svn_wcprops.h"
#include "FieldLoader.h"
#include "ContentFieldImpl.h"

class CSvnFieldLoader : public CFieldLoader
{
public:
	CSvnFieldLoader();
	virtual ~CSvnFieldLoader();

	virtual CContentField& getFieldByIndex(int iIdx);

private:
	TContentFieldImpl<ft_string> m_fieldAuthor;
};

#endif
