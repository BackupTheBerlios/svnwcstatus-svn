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

#include "svn_wcstatus.h"
#include "SvnFieldLoader.h"

#include "SmartPtr.h"

#include "apr_general.h"

static HINSTANCE g_hInstDll = NULL;
static CFieldLoader* g_pLoader = NULL;

static bool dllProcessAttach(HINSTANCE hInstDll)
{
	if (!hInstDll)
		return false;

	g_hInstDll = hInstDll;

	if (!DisableThreadLibraryCalls(g_hInstDll))
		return false;

	if (apr_initialize() != APR_SUCCESS)
		return false;

	return true;
}

static bool dllProcessDetach()
{
	if (g_pLoader)
	{
		delete g_pLoader;
		g_pLoader = NULL;
	}

	apr_terminate();

	g_hInstDll = NULL;

	return true;
}

BOOL APIENTRY DllMain(HINSTANCE hInstDll, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		return dllProcessAttach(hInstDll) ? TRUE : FALSE;

	case DLL_PROCESS_DETACH:
		return dllProcessDetach() ? TRUE : FALSE;

	default:
		return TRUE;
	}
}

int __stdcall ContentGetSupportedField(int iFieldIdx, char* pchName, char* pchUnits, int iMaxBuf)
{
	try
	{
		const CContentField& oField = g_pLoader->getFieldByIndex(iFieldIdx);
		return oField.fillInDefinition(pchName, pchUnits, iMaxBuf);
	}
	catch (CFieldLoader::Ex* e)
	{
		delete e;
		return ft_nomorefields;
	}
}

int __stdcall ContentGetValue(char* pchPath, int iFieldIdx, int iUnitIdx, void* pValue, int iMaxBuf, int iFlags)
{
	try
	{
		TSmartPtr<CContentInstance> pTheInstance(g_pLoader->getFieldByIndex(iFieldIdx).getInstance(pchPath));
		return pTheInstance->copyValueTo(&pValue, iMaxBuf);
	}
	catch (CFieldLoader::Ex* e)
	{
		delete e;
		return ft_nosuchfield;
	}
	catch (CSvnEx* e)
	{
		delete e;
		return ft_nosuchfield;
	}
}

void __stdcall ContentSetDefaultParams(ContentDefaultParamStruct* psParams)
{
	if (g_pLoader)
	{
		delete g_pLoader;
		g_pLoader = NULL;
	}

	g_pLoader = new CSvnFieldLoader(*psParams, g_hInstDll);
}
