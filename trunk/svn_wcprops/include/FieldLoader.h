#ifndef __TW_WDX_SVN_WCPROPS_FILELOADER__
#define __TW_WDX_SVN_WCPROPS_FILELOADER__

#include "svn_wcprops.h"
#include "ContentField.h"
#include "ContentInstance.h"

class CFieldLoader  
{
public:
	enum ex_e
	{
		exNoSuchFieldIndex
	};

	class Ex
	{
	public:
		Ex(ex_e eNum);

		ex_e getCause() const;

	private:
		ex_e m_eCause;
	};

	virtual ~CFieldLoader();

	virtual const CContentField& getFieldByIndex(int iIdx) = 0;
	virtual CContentInstancePtr getInstanceByFile(const CContentField& oRequestedType, const char* pchFile) = 0;
};

#endif