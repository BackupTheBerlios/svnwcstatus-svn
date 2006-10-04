#ifndef __TW_WDX_SVN_WCPROPS_MULTICHOICEDEFSCHEDULE__
#define __TW_WDX_SVN_WCPROPS_MULTICHOICEDEFSCHEDULE__

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
