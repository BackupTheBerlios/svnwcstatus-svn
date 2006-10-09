#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELD__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELD__

#include "ContentInstance.h"

class CMultiChoiceDef;

class CContentField
{
public:
	virtual ~CContentField();

	virtual const char* getName() const = 0;
	virtual int getType() const = 0;

	virtual bool hasMultiChoiceDef() const;
	virtual const CMultiChoiceDef* getMultiChoiceDef() const;
	virtual void getUnits(char* pchUnits, int iMaxBuf) const;

	virtual void fillInDefinition(char* pchName, char* pchUnits, int iMaxBuf) const;

	virtual CContentInstance* getInstance(const char* pchPath) = 0;
};

#endif
