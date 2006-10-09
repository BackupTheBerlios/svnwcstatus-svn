#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCE__
#define __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCE__

#include "svn_wcstatus.h"

class CContentField;

class CContentInstance
{
public:
	virtual ~CContentInstance();

	const CContentField& getType() const;
	virtual int copyValueTo(void** ppBuf, int iMaxBuf) const = 0;

protected:
	const CContentField& m_oField;
	char m_achFile[_MAX_PATH];

	CContentInstance(const CContentField& oField, const char* pchPath);
};

#endif