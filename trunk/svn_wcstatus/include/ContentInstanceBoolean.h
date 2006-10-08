#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCEBOOLEAN__
#define __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCEBOOLEAN__

#include "svn_wcstatus.h"
#include "ContentInstance.h"

class CContentInstanceBoolean : public CContentInstance
{
public:
	CContentInstanceBoolean(const CContentField& oField, const char* pchPath);
	CContentInstanceBoolean(const CContentField& oField, const char* pchPath, bool bValue);
	CContentInstanceBoolean(const CContentField& oField, const char* pchPath, bool* pbValue);
	virtual ~CContentInstanceBoolean();

	virtual int copyValueTo(void** ppBuf, int iMaxBuf) const;

private:
	char m_nValue;
};

#endif
