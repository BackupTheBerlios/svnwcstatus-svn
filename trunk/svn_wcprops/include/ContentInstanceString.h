#ifndef __TW_WDX_SVN_WCPROPS_CONTENTINSTANCESTRING__
#define __TW_WDX_SVN_WCPROPS_CONTENTINSTANCESTRING__

#include "svn_wcprops.h"
#include "ContentInstance.h"

class CContentInstanceString : public CContentInstance
{
public:
	CContentInstanceString(const CContentField& oField, const char* pchFile, const char* pchValue);
	virtual ~CContentInstanceString();

	virtual int copyValueTo(void** ppBuf, int iMaxBuf) const;

protected:
	char* m_achValue;
};

typedef TSmartPtr<CContentInstanceString> CContentInstanceStringPtr;

#endif