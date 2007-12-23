/* Copyright 2007, 2008 Tom Wieczorek
 *
 * This file is part of svn_wcstatus.
 *
 * svn_wcstatus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * svn_wcstatus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with svn_wcstatus. If not, see <http://www.gnu.org/licenses/>.
 */

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
