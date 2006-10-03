#ifndef __TW_WDX_SVN_WCPROPS_CONTENTINSTANCEBOOLEAN__
#define __TW_WDX_SVN_WCPROPS_CONTENTINSTANCEBOOLEAN__

#include "svn_wcprops.h"
#include "ContentInstance.h"

class CContentInstanceBoolean : public CContentInstance
{
public:
	CContentInstanceBoolean(const CContentField& oField, const char* pchFile);
	CContentInstanceBoolean(const CContentField& oField, const char* pchFile, bool bValue);
	CContentInstanceBoolean(const CContentField& oField, const char* pchFile, bool* pbValue);
	virtual ~CContentInstanceBoolean();

	virtual int copyValueTo(void** ppBuf, int iMaxBuf) const;

private:
	char m_nValue;
};

#endif
