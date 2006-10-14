#include "svn_wcstatus.h"
#include "SvnFieldLoader.h"

#include "SmartPtr.h"

#include "apr_general.h"

static CFieldLoader* g_pLoader;

static bool dllProcessAttach()
{
	HMODULE hModule = GetModuleHandle(MODULE_NAME);

	if (!hModule)
		return false;

	if (!DisableThreadLibraryCalls(hModule))
		return false;

	if (apr_initialize() != APR_SUCCESS)
		return false;

	try
	{
		g_pLoader = new CSvnFieldLoader();
	}
	catch (...)
	{
		apr_terminate();
		return false;
	}

	return true;
}

static bool dllProcessDetach()
{
	delete g_pLoader;
	apr_terminate();
	return true;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		return dllProcessAttach() ? TRUE : FALSE;

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
	if (psParams)
		g_pLoader->initParameters(*psParams);
}
