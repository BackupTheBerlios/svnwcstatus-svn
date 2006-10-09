#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCENUMERIC32__
#define __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCENUMERIC32__

#include "svn_wcstatus.h"
#include "ContentInstance.h"

class CContentInstanceNumeric32 : public CContentInstance
{
public:
	CContentInstanceNumeric32(const CContentField& oField, const char* pchPath, int iValue);
	virtual ~CContentInstanceNumeric32();

	virtual int copyValueTo(void** ppBuf, int iMaxBuf) const;

private:
	int m_nValue;
};

#endif
