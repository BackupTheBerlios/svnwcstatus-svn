#include "svn_wcprops.h"
#include "SvnFieldLoader.h"

CSvnFieldLoader g_oLoader;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
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