#ifndef __TW_WDX_SVN_WCPROPS_CONTENTFIELDSVNSTATUS__
#define __TW_WDX_SVN_WCPROPS_CONTENTFIELDSVNSTATUS__

#include "ContentFieldSvnMultiChoice.h"

class CContentFieldSvnTextStatus : public CContentFieldSvnMultiChoice
{
public:
	CContentFieldSvnTextStatus(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnTextStatus();

	virtual const char* getName() const;

	virtual CContentInstancePtr getInstance(const char* pchPath);
};

#endif
