#ifndef __TW_WDX_SVN_WCPROPS__
#define __TW_WDX_SVN_WCPROPS__

#include <windows.h>
#include <stdlib.h>

#include "contentplug.h"

#include "SmartPtr.h"

int __stdcall ContentGetSupportedField(int iFieldIdx, char* pchName, char* pchUnits, int iMaxBuf);
int __stdcall ContentGetValue(char* pchFile, int iFieldIdx, int iUnitIdx, void* pValue, int iMaxBuf, int iFlags);

#endif