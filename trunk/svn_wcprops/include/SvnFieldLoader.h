#ifndef __TW_WDX_SVN_WCPROPS_SVNFIELDLOADER__
#define __TW_WDX_SVN_WCPROPS_SVNFIELDLOADER__

#include "svn_wcprops.h"
#include "FieldLoader.h"
#include "ContentFieldInstance.h"

class CSvnFieldLoader : public CFieldLoader
{
public:
	CSvnFieldLoader();
	virtual ~CSvnFieldLoader();

	virtual const CContentField& getFieldByIndex(int iIdx);
	virtual CContentInstancePtr getInstanceByFile(const CContentField& oRequestedType, const char* pchFile);

private:
	TContentFieldInstance<ft_string> m_fieldAuthor;

	CContentInstancePtr instanciateAuthor(const char* pchFile);
};

#endif