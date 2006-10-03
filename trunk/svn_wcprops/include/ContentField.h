#ifndef __TW_WDX_SVN_WCPROPS_CONTENTFIELD__
#define __TW_WDX_SVN_WCPROPS_CONTENTFIELD__

#include "ContentInstance.h"

class CContentField
{
public:
	virtual ~CContentField();

	virtual const char* getName() const = 0;
	virtual int getType() const = 0;

	virtual CContentInstancePtr getInstance(const char* pchPath) = 0;
};

typedef TSmartPtr<CContentField> CContentFieldPtr;

#endif