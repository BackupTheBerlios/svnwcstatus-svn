#include "svn_wcprops.h"
#include "SvnFieldLoader.h"

#include <apr_general.h>

CSvnFieldLoader g_oLoader;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		return apr_initialize() == APR_SUCCESS ? TRUE : FALSE;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_DETACH:
		apr_terminate();
		return TRUE;

	default:
		return TRUE;
	}
}

int __stdcall ContentGetSupportedField(int iFieldIdx, char* pchName, char* pchUnits, int iMaxBuf)
{
	try
	{
		const CContentField& oField = g_oLoader.getFieldByIndex(iFieldIdx);

		if (iMaxBuf > 0 && pchName)
		{
			strncpy(pchName, oField.getName(), iMaxBuf);
			pchName[iMaxBuf - 1] = '\0';
		}

		return oField.getType();
	}
	catch (CFieldLoader::Ex* e)
	{
		delete e;
		return ft_nomorefields;
	}
}

int __stdcall ContentGetValue(char* pchFile, int iFieldIdx, int iUnitIdx, void* pValue, int iMaxBuf, int iFlags)
{
	try
	{
		CContentInstancePtr pTheInstance = g_oLoader.getFieldByIndex(iFieldIdx).getInstance(pchFile);

		return pTheInstance->copyValueTo(&pValue, iMaxBuf);
	}
	catch (CFieldLoader::Ex* e)
	{
		delete e;
		return ft_nosuchfield;
	}
}