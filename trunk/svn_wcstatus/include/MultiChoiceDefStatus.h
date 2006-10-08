#ifndef __TW_WDX_SVN_WCSTATUS_MULTICHOICEDEFSTATUS__
#define __TW_WDX_SVN_WCSTATUS_MULTICHOICEDEFSTATUS__

#include "MultiChoiceDef.h"

class CMultiChoiceDefStatus : public CMultiChoiceDef
{
public:
	CMultiChoiceDefStatus(CContentField& oForField);
	virtual ~CMultiChoiceDefStatus();

	virtual size_t getChoiceCount() const;
	virtual const char* getChoiceName(int iChoice) const;
};

#endif
