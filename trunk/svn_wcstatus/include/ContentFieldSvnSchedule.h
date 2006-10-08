#ifndef __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSCHEDULE__
#define __TW_WDX_SVN_WCSTATUS_CONTENTFIELDSVNSCHEDULE__

#include "ContentFieldSvnMultiChoice.h"

class CMultiChoiceDef;

class CContentFieldSvnSchedule : public CContentFieldSvnMultiChoice
{
public:
	CContentFieldSvnSchedule(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnSchedule();

	virtual const char* getName() const;

	virtual CContentInstancePtr getInstance(const char* pchPath);
};

#endif
