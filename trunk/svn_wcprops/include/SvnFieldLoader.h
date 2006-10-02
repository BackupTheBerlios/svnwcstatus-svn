#ifndef __TW_WDX_SVN_WCPROPS_SVNFIELDLOADER__
#define __TW_WDX_SVN_WCPROPS_SVNFIELDLOADER__

#include "FieldLoader.h"

class CSvnFieldLoader : public CFieldLoader
{
public:
	CSvnFieldLoader();
	virtual ~CSvnFieldLoader();

	virtual CContentField& getFieldByIndex(int iIdx);

private:
	CContentField** m_pFields;
	size_t m_nFieldCount;
};

#endif
