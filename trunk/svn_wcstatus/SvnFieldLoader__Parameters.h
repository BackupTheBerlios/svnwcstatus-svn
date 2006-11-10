#ifndef __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__PARAMETERS__
#define __TW_WDX_SVN_WCSTATUS_SVNFIELDLOADER__PARAMETERS__

#include "SvnFieldLoader.h"

#include "SvnPool.h"

struct apr_hash_t;

class CSvnFieldLoader::CParameters
{
public:
	CParameters(const ContentDefaultParamStruct& sParams);
	virtual ~CParameters();

	bool shouldTweakExternalStatus() const;

	void clearParamCache();

private:
	CSvnPool m_oPool;
	const char* m_pchIniFilePath;
	bool m_bTweakExtStatuses;

	void determineIniFilePath(const char* pchIniFilePathTc);
	void checkIniFile();
	void writeNewIniFile() const;

	void readGeneralSettings();

	apr_hash_t* readIniSect(const char* pchIniSectName, apr_pool_t* pPool);
};

#endif
