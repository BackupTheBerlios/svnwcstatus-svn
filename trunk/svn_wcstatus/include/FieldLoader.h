#ifndef __TW_WDX_SVN_WCSTATUS_FILELOADER__
#define __TW_WDX_SVN_WCSTATUS_FILELOADER__

#include "svn_wcstatus.h"
#include "ContentField.h"
#include "ContentInstance.h"

class CFieldLoader
{
public:
	enum ex_e
	{
		exNoSuchFieldIndex,
		exNoSuchField
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

	virtual CContentField& getFieldByIndex(int iIdx) = 0;
	virtual size_t getFieldCount() const = 0;

	virtual void initParameters(const ContentDefaultParamStruct& sParams) = 0;
};

#endif
