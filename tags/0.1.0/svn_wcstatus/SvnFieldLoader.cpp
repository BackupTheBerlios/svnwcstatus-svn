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

#include "SvnFieldLoader.h"
#include "SvnFieldLoader__Parameters.h"
#include "SvnFieldLoader__EntryCache.h"
#include "ContentFieldSvnRevision.h"
#include "ContentFieldSvnCmtAuthor.h"
#include "ContentFieldSvnCmtRev.h"
#include "ContentFieldSvnCmtTime.h"
#include "ContentFieldSvnStatusText.h"
#include "ContentFieldSvnStatusProps.h"
#include "ContentFieldSvnSchedule.h"
#include "ContentFieldSvnUrl.h"
#include "ContentFieldSvnRepos.h"
#include "ContentFieldSvnUuid.h"
#include "ContentFieldSvnCopied.h"
#include "ContentFieldSvnDeleted.h"
#include "ContentFieldSvnAbsent.h"
#include "ContentFieldSvnIncomplete.h"
#include "ContentFieldSvnTextTime.h"
#include "ContentFieldSvnPropTime.h"
#include "ContentFieldSvnLockToken.h"
#include "ContentFieldSvnLockOwner.h"
#include "ContentFieldSvnLockComment.h"
#include "ContentFieldSvnLockCreationDate.h"
#include "ContentFieldSvnPresentProps.h"
#include "ContentFieldSvnProp.h"

#include "svn_pools.h"
#include "svn_path.h"
#include "svn_client.h"

#define INITIAL_FIELD_ARRAY_SIZE 30

static int cleanupFieldArray(void* pData)
{
	apr_array_header_t* pArray = static_cast<apr_array_header_t*>(pData);

	for (int i = 0; i < pArray->nelts; ++i)
	{
		delete APR_ARRAY_GET(pArray, i, CContentFieldSvn*);
	}

	return APR_SUCCESS;
}

CSvnFieldLoader::CSvnFieldLoader(const ContentDefaultParamStruct& sParams, HINSTANCE hInstDll) :
	m_hInstDll(hInstDll),
	m_oPool(),
	m_pFields(NULL),
	m_pClientCtx(NULL),
	m_pParams(new CParameters(sParams)),
	m_pLastEntry(NULL)
{
	SVN_EX(svn_client_create_context(&m_pClientCtx, m_oPool));

	emptyContentFields(INITIAL_FIELD_ARRAY_SIZE);
	appendDefaultContentFields();
	appendDynamicContentFields();

	initAprIconvDsoPath();
}

CSvnFieldLoader::~CSvnFieldLoader()
{
	if (m_pLastEntry)
	{
		delete m_pLastEntry;
	}

	if (m_pParams)
	{
		delete m_pParams;
	}
}

CContentField& CSvnFieldLoader::getFieldByIndex(int iIdx)
{
	if (iIdx < 0 || (size_t)iIdx >= getFieldCount())
	{
		throw new CFieldLoader::Ex(CFieldLoader::exNoSuchFieldIndex);
	}

	return *getField(iIdx);
}

size_t CSvnFieldLoader::getFieldCount() const
{
	return m_pFields ? m_pFields->nelts : 0;
}

CContentFieldSvn* CSvnFieldLoader::getField(int iIdx)
{
	return APR_ARRAY_GET(m_pFields, iIdx, CContentFieldSvn*);
}

void CSvnFieldLoader::appendField(CContentFieldSvn* pField)
{
	APR_ARRAY_APPEND(m_pFields, pField, CContentFieldSvn*);
}

void CSvnFieldLoader::emptyContentFields(int iInitialArrayLen)
{
	apr_pool_t* pPool;

	if (!m_pFields)
	{
		pPool = svn_pool_create(m_oPool);
	}
	else
	{
		pPool = m_pFields->pool;
		svn_pool_clear(pPool);
	}

	m_pFields = apr_array_make(pPool, iInitialArrayLen, sizeof (CContentFieldSvn*));
	apr_pool_cleanup_register(m_pFields->pool, m_pFields, cleanupFieldArray, NULL);
}

void CSvnFieldLoader::appendDefaultContentFields()
{
	appendField(new CContentFieldSvnRevision(*this));
	appendField(new CContentFieldSvnRevision(*this));
	appendField(new CContentFieldSvnCmtAuthor(*this));
	appendField(new CContentFieldSvnCmtRev(*this));
	appendField(new CContentFieldSvnCmtTime(*this));
	appendField(new CContentFieldSvnStatusText(*this));
	appendField(new CContentFieldSvnStatusProps(*this));
	appendField(new CContentFieldSvnSchedule(*this));
	appendField(new CContentFieldSvnUrl(*this));
	appendField(new CContentFieldSvnRepos(*this));
	appendField(new CContentFieldSvnUuid(*this));
	appendField(new CContentFieldSvnCopied(*this));
	appendField(new CContentFieldSvnDeleted(*this));
	appendField(new CContentFieldSvnAbsent(*this));
	appendField(new CContentFieldSvnIncomplete(*this));
	appendField(new CContentFieldSvnTextTime(*this));
	appendField(new CContentFieldSvnPropTime(*this));
	appendField(new CContentFieldSvnLockToken(*this));
	appendField(new CContentFieldSvnLockOwner(*this));
	appendField(new CContentFieldSvnLockComment(*this));
	appendField(new CContentFieldSvnLockCreationDate(*this));
	appendField(new CContentFieldSvnPresentProps(*this));
}

void CSvnFieldLoader::appendDynamicContentFields()
{
	CSvnPool oPool;
	apr_hash_t* pProps = m_pParams->getProps();

	if (!pProps)
		return;

	for (apr_hash_index_t* pIdx = apr_hash_first(oPool, pProps); pIdx; pIdx = apr_hash_next(pIdx))
	{
		const char* pchPropName;
		char* pchFieldName;
		int iSize = 0;

		apr_hash_this(pIdx, reinterpret_cast<const void**>(&pchPropName), &iSize, reinterpret_cast<void**>(&pchFieldName));
		appendField(new CContentFieldSvnProp(*this, pchPropName, pchFieldName));
	}
}

void CSvnFieldLoader::initAprIconvDsoPath()
{
	const char* pchTweak = m_pParams->getTweakAprIconvPath();
	if (!pchTweak || *pchTweak == '\0' || apr_strnatcasecmp(pchTweak, "no") == 0)
	{
		return;
	}

	char achTempPath[_MAX_PATH + 1];

	if (apr_strnatcasecmp(pchTweak, "yes")  == 0)
	{
		const char* pchPath = m_pParams->getAprIconvPath();
		if (!pchPath || *pchPath == '\0') return;
		apr_cpystrn(achTempPath, pchPath, sizeof (achTempPath));
	}
	else if (apr_strnatcasecmp(pchTweak, "plugin_dir") == 0)
	{
		HMODULE hModule = GetModuleHandle(MODULE_NAME);
		
		if (!hModule)
			return;

		DWORD dwRes = GetModuleFileName(hModule, achTempPath, sizeof (achTempPath));

		if (dwRes < 1)
		{
			// we cannot do anything about that error...
			return;
		}

		// replace module file name with default path to apr-iconv DSOs
		size_t nPos = dwRes - 1;
		while (nPos)
		{
			if (achTempPath[nPos] == '\\')
			{
				strncpy(achTempPath + nPos + 1, "iconv", sizeof (achTempPath) - nPos - 1);
				break;
			}
			--nPos;
		}

		if (nPos == 0)
		{
			// no or leading backslash in module path!?!
			return;
		}

		achTempPath[sizeof (achTempPath) - 1] = '\0';
	}
	else
	{
		// no known option found, simply return...
		return;
	}

	// check for directory existence
	DWORD dwRes = GetFileAttributes(achTempPath);
	if (dwRes != MAXDWORD && (dwRes & FILE_ATTRIBUTE_DIRECTORY))
	{
		// ignore errors here...
		SetEnvironmentVariable("APR_ICONV_PATH", achTempPath);
	}
}

CSvnFieldLoader::CEntryCache* CSvnFieldLoader::getCacheForPath(const char* pchPath)
{
	return m_pLastEntry ?
		(m_pLastEntry->isPath(pchPath) ? m_pLastEntry : m_pLastEntry->switchPath(pchPath)) :
		(m_pLastEntry = new CEntryCache(*this, pchPath));
}

svn_wc_status2_t* CSvnFieldLoader::getStatusForPath(const char* pchPath, apr_pool_t* pPool)
{
	CSvnPool oSubpool;

	const char* pchInternalPath = svn_path_internal_style(pchPath, oSubpool);
	const char* pchBaseName = svn_path_basename(pchInternalPath, oSubpool);

	if (svn_wc_is_adm_dir(pchBaseName, oSubpool))
	{
		return NULL;
	}

	return getCacheForPath(svn_path_dirname(pchInternalPath, oSubpool))->getStatus(pchBaseName);
}

apr_hash_t* CSvnFieldLoader::getPropsForPath(const char* pchPath, apr_pool_t* pPool)
{
	CSvnPool oSubpool;

	const char* pchInternalPath = svn_path_internal_style(pchPath, oSubpool);
	const char* pchBaseName = svn_path_basename(pchInternalPath, oSubpool);

	if (svn_wc_is_adm_dir(pchBaseName, oSubpool))
	{
		return NULL;
	}

	return getCacheForPath(svn_path_dirname(pchInternalPath, oSubpool))->getProps(pchBaseName);
}

void CSvnFieldLoader::aprTimeToFileTime(apr_time_t nTime, FILETIME& ftTime) const
{
	// XXX error handling?

	apr_time_exp_t sAprTime = {0};
	apr_time_exp_gmt(&sAprTime, nTime);

	SYSTEMTIME sSysTime = 
	{
		sAprTime.tm_year + 1900,  // wYear
		sAprTime.tm_mon + 1,      // wMonth
		0,                        // wDayOfWeek
		sAprTime.tm_mday,         // wDay
		sAprTime.tm_hour,         // wHour
		sAprTime.tm_min,          // wMinute
		sAprTime.tm_sec,          // wSecond
		sAprTime.tm_usec / 1000   // wMilliseconds
	};

	SystemTimeToFileTime(&sSysTime, &ftTime);
}

/*
svn_wc_status2_t* CSvnFieldLoader::dupEntry(svn_wc_status2_t* pEntry, apr_pool_t* pPool)
{
	return pEntry ? svn_wc_dup_status2(pEntry, pPool) : NULL;
}
*/
#undef INITIAL_FIELD_ARRAY_SIZE
