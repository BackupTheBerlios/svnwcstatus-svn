#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCEDATETIME__
#define __TW_WDX_SVN_WCSTATUS_CONTENTINSTANCEDATETIME__

#include "svn_wcstatus.h"
#include "ContentInstance.h"

class CContentInstanceDateTime : public CContentInstance
{
public:
	CContentInstanceDateTime(const CContentField& oField, const char* pchPath, const FILETIME& ftValue);
	virtual ~CContentInstanceDateTime();

	virtual int copyValueTo(void** ppBuf, int iMaxBuf) const;

private:
	FILETIME m_ftValue;
};

#endif
