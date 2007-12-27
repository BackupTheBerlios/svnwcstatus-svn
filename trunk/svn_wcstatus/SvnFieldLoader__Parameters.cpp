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

#include "SvnFieldLoader__Parameters.h"

#include "SvnPool.h"

#include "apr_file_io.h"
#include "svn_pools.h"
#include "svn_path.h"
#include "svn_io.h"

#define INI_FILE_NAME "svn_wcstatus.ini"
#define INI_SECT_GENERAL "general"
#define INI_KEY_GENERAL_TWEAK_API_PATH "tweak_apr_iconv_path"
#define INI_KEY_GENERAL_API_PATH "apr_iconv_path"
#define INI_KEY_GENERAL_TWEAK_EXT_STATUSES "tweak_external_statuses"
#define INI_SECT_DYNPROPS "dynamic_properties"

CSvnFieldLoader::CParameters::CParameters(const ContentDefaultParamStruct& sParams) :
	m_oPool(),
	m_pchIniFilePath(NULL),
	m_bTweakExtStatuses(false)
{
	determineIniFilePath(sParams.DefaultIniName);

	// if m_pchIniFilePath == NULL, determineIniFilePath() failed.
	if (m_pchIniFilePath)
	{
		checkIniFile();
		readGeneralSettings();
	}
}

CSvnFieldLoader::CParameters::~CParameters()
{
}

void CSvnFieldLoader::CParameters::determineIniFilePath(const char* pchIniFilePathTc)
{
	CSvnPool oSubpool(m_oPool);
	const char* pchDir;
	char* pchFile;

	try
	{
		SVN_EX(svn_path_split_if_file(
			svn_path_internal_style(pchIniFilePathTc, oSubpool),
			&pchDir, const_cast<const char**>(&pchFile), oSubpool));

		if (apr_filepath_merge(&pchFile, pchDir, INI_FILE_NAME,
		                       (APR_FILEPATH_NOTRELATIVE |
		                       APR_FILEPATH_TRUENAME),
		                       oSubpool) != APR_SUCCESS)
		{
			throw new CSvnEx(NULL);
		}
	}
	catch (CSvnEx* e)
	{
		delete e;

		// Inform the class that ini file path resolution failed.
		m_pchIniFilePath = NULL;
		return;
	}

	m_pchIniFilePath = svn_path_local_style(pchFile, m_oPool);
}

void CSvnFieldLoader::CParameters::checkIniFile()
{
	// check existence
	DWORD dwAttrs = GetFileAttributes(m_pchIniFilePath);
	if (dwAttrs == MAXDWORD)
	{
		DWORD dwErr = GetLastError();

		if ((dwErr == ERROR_FILE_NOT_FOUND) || (dwErr == ERROR_PATH_NOT_FOUND))
		{
			writeNewIniFile();
		}
	}
}

void CSvnFieldLoader::CParameters::writeNewIniFile() const
{
	CSvnPool oPool;

	const char * const pchContents =
		"; This is the configuration file for the Total Commander Content PlugIn " PLUGIN_NAME "." APR_EOL_STR
		APR_EOL_STR
		"[" INI_SECT_GENERAL "]" APR_EOL_STR
		";" INI_KEY_GENERAL_TWEAK_EXT_STATUSES "=yes" APR_EOL_STR;

	apr_file_t* pFile;
	apr_size_t nWritten;

	SVN_EX(svn_io_file_open(&pFile, m_pchIniFilePath ,
	                        (APR_WRITE | APR_CREATE | APR_EXCL),
	                        APR_OS_DEFAULT, oPool));

	SVN_EX(svn_io_file_write_full(pFile, pchContents, strlen(pchContents),
	                              &nWritten, oPool));

	SVN_EX(svn_io_file_close(pFile, oPool));
}

apr_hash_t* CSvnFieldLoader::CParameters::readIniSect(const char* pchIniSectName, apr_pool_t* pPool)
{
	// XXX error handling?

	char achSectData[32768] = {0};
	size_t nSize = GetPrivateProfileSection(pchIniSectName, achSectData,
	                                        sizeof (achSectData),
	                                        m_pchIniFilePath);

	apr_hash_t* pSect = apr_hash_make(pPool);
	apr_pool_t* pSectPool = apr_hash_pool_get(pSect);

	for (char* pchCur = achSectData; *pchCur; ++pchCur)
	{
		char* pchOffset = strchr(pchCur, '=');
		if (pchOffset)
		{
			int iKeyLen = pchOffset - pchCur;
			if (iKeyLen > 0)
			{
				const char* pchKey = apr_pstrndup(pSectPool, pchCur, iKeyLen);
				const char* pchValue = apr_pstrdup(pSectPool, pchOffset + 1 ? pchOffset + 1 : "");
				apr_hash_set(pSect, pchKey, APR_HASH_KEY_STRING, pchValue);
			}
		}

		pchCur += strlen(pchCur);
	}

	return pSect;
}

void CSvnFieldLoader::CParameters::readGeneralSettings()
{
	CSvnPool oTempPool;
	apr_hash_t* pGeneral = readIniSect(INI_SECT_GENERAL, oTempPool);

	const char* pchVal = static_cast<const char*>(
		apr_hash_get(pGeneral, INI_KEY_GENERAL_TWEAK_EXT_STATUSES, APR_HASH_KEY_STRING));
	m_bTweakExtStatuses = pchVal && apr_strnatcasecmp(pchVal, "yes") == 0 ? true : false;
}

bool CSvnFieldLoader::CParameters::shouldTweakExternalStatus() const
{
	return m_bTweakExtStatuses;
}

void CSvnFieldLoader::CParameters::clearParamCache()
{
	char* pchTmpIniPath = strdup(m_pchIniFilePath);
	m_oPool.clear();
	m_pchIniFilePath = apr_pstrdup(m_oPool, pchTmpIniPath);
	free(pchTmpIniPath);

	m_bTweakExtStatuses = false;
}
