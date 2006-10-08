#ifndef __TW_WDX_SVN_WCSTATUS_MULTICHOICEDEFSCHEDULE__
#define __TW_WDX_SVN_WCSTATUS_MULTICHOICEDEFSCHEDULE__

#include "MultiChoiceDef.h"

class CMultiChoiceDefSchedule : public CMultiChoiceDef
{
public:
	CMultiChoiceDefSchedule(CContentField& oForField);
	virtual ~CMultiChoiceDefSchedule();

	virtual size_t getChoiceCount() const;
	virtual const char* getChoiceName(int iChoice) const;
};

#endif
