#include "svn_wcprops.h"
#include "SvnFieldLoader.h"

#include <apr_general.h>

static CSvnFieldLoader* g_pLoader;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (apr_initialize() != APR_SUCCESS)
		{
			return FALSE;
		}

		try
		{
			g_pLoader = new CSvnFieldLoader();
		}
		catch (...)
		{
			apr_terminate();
			return FALSE;
		}

		return TRUE;

	case DLL_PROCESS_DETACH:
		delete g_pLoader;
		apr_terminate();
		return TRUE;

	// currently unused
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		return TRUE;

	default:
		return TRUE;
	}
}

int __stdcall ContentGetSupportedField(int iFieldIdx, char* pchName, char* pchUnits, int iMaxBuf)
{
	try
	{
		const CContentField& oField = g_pLoader->getFieldByIndex(iFieldIdx);
		oField.fillInDefinition(pchName, pchUnits, iMaxBuf);


		return oField.getType();
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
		CContentInstancePtr pTheInstance = g_pLoader->getFieldByIndex(iFieldIdx).getInstance(pchPath);

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
