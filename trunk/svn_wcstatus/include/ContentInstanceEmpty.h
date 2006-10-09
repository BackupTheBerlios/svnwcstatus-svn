#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCEEMPTY__
#define __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCEEMPTY__

#include "ContentInstance.h"

class CContentInstanceEmpty : public CContentInstance
{
public:
	CContentInstanceEmpty(const CContentField& oField, const char* pchFile);
	virtual ~CContentInstanceEmpty();

	virtual int copyValueTo(void** ppBuf, int iMaxBuf) const;
};

#endif
