#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCESTRING__
#define __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCESTRING__

#include "svn_wcstatus.h"
#include "ContentInstance.h"

class CContentInstanceString : public CContentInstance
{
public:
	CContentInstanceString(const CContentField& oField, const char* pchPath, const char* pchValue);
	CContentInstanceString(const CContentField& oField, const char* pchPath, const char* pchValue, size_t nLen);
	virtual ~CContentInstanceString();

	virtual int copyValueTo(void** ppBuf, int iMaxBuf) const;

protected:
	char* m_achValue;
};

#endif