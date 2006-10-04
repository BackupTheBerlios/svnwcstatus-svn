#ifndef __TW_WDX_SVN_WCPROPS_CONTENTINSTANCEMULTICHOICE__
#define __TW_WDX_SVN_WCPROPS_CONTENTINSTANCEMULTICHOICE__

#include "svn_wcprops.h"
#include "ContentInstance.h"

class CMultiChoiceDef;

class CContentInstanceMultiChoice : public CContentInstance
{
public:
	CContentInstanceMultiChoice(const CMultiChoiceDef& oDef, const char* pchPath, int iChoice);
	virtual ~CContentInstanceMultiChoice();

	virtual int copyValueTo(void** ppBuf, int iMaxBuf) const;

private:
	const CMultiChoiceDef& m_oDef;
	int m_iChoiceItem;
};

#endif
