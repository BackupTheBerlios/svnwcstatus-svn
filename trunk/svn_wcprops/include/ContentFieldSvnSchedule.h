#ifndef __TW_WDX_SVN_WCPROPS_CONTENTFIELDSVNSCHEDULE__
#define __TW_WDX_SVN_WCPROPS_CONTENTFIELDSVNSCHEDULE__

#include "ContentFieldSvn.h"

class CMultiChoiceDef;

class CContentFieldSvnSchedule : public CContentFieldSvn
{
public:
	CContentFieldSvnSchedule(CSvnFieldLoader& oLoader);
	virtual ~CContentFieldSvnSchedule();

	virtual const char* getName() const;
	virtual int getType() const;

	const CMultiChoiceDef* getMultiChoiceDef() const;
	
	virtual CContentInstancePtr getInstance(const char* pchPath);

private:
	CMultiChoiceDef* m_pDef;
};

#endif
