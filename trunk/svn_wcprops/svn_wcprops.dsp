# Microsoft Developer Studio Project File - Name="svn_wcprops" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=svn_wcprops - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "svn_wcprops.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "svn_wcprops.mak" CFG="svn_wcprops - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "svn_wcprops - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "svn_wcprops - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "svn_wcprops - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bin"
# PROP Intermediate_Dir "bin\Intermediate\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SVN_WCPROPS_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "include" /I "..\totalcmd\include" /I "..\subversion\include\apr" /I "..\subversion\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "APR_DECLARE_STATIC" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib advapi32.lib ws2_32.lib shell32.lib libapr.lib libaprutil.lib xml.lib zlibstat.lib libsvn_subr-1.lib libsvn_delta-1.lib libsvn_diff-1.lib libsvn_fs-1.lib libsvn_fs_fs-1.lib libsvn_repos-1.lib libsvn_ra-1.lib libsvn_ra_local-1.lib libsvn_wc-1.lib libsvn_client-1.lib /nologo /dll /machine:I386 /out:"bin/svn_wcprops.wdx" /libpath:"..\subversion\lib\bdb" /libpath:"..\subversion\lib\apr" /libpath:"..\subversion\lib\apr-util" /libpath:"..\subversion\lib\neon" /libpath:"..\subversion\lib"

!ELSEIF  "$(CFG)" == "svn_wcprops - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "bin"
# PROP Intermediate_Dir "bin\Intermediate\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SVN_WCPROPS_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "include" /I "..\totalcmd\include" /I "..\subversion\include\apr" /I "..\subversion\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "APR_DECLARE_STATIC" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"bin/svn_wcpropsD.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib advapi32.lib ws2_32.lib shell32.lib libapr.lib libaprutil.lib xml.lib zlibstat.lib libsvn_subr-1.lib libsvn_delta-1.lib libsvn_diff-1.lib libsvn_fs-1.lib libsvn_fs_fs-1.lib libsvn_repos-1.lib libsvn_ra-1.lib libsvn_ra_local-1.lib libsvn_wc-1.lib libsvn_client-1.lib /nologo /dll /debug /machine:I386 /out:"bin/svn_wcpropsD.wdx" /pdbtype:sept /libpath:"..\subversion\lib\bdb" /libpath:"..\subversion\lib\apr" /libpath:"..\subversion\lib\apr-util" /libpath:"..\subversion\lib\neon" /libpath:"..\subversion\lib"

!ENDIF 

# Begin Target

# Name "svn_wcprops - Win32 Release"
# Name "svn_wcprops - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;rc;def;odl;idl;bat"
# Begin Source File

SOURCE=.\ContentField.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentFieldSvn.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentFieldSvnAuthor.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentFieldSvnIgnored.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentFieldSvnMultiChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentFieldSvnSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentFieldSvnTextStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentInstance.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentInstanceBoolean.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentInstanceMultiChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\ContentInstanceString.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiChoiceDef.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiChoiceDefSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiChoiceDefStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\svn_wcprops.cpp
# End Source File
# Begin Source File

SOURCE=.\svn_wcprops.def
# End Source File
# Begin Source File

SOURCE=.\SvnEx.cpp
# End Source File
# Begin Source File

SOURCE=.\SvnFieldLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\SvnFieldLoader__EntryCache.cpp
# End Source File
# Begin Source File

SOURCE=.\SvnPool.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;inl"
# Begin Source File

SOURCE=.\include\ContentField.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentFieldSvn.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentFieldSvnAuthor.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentFieldSvnIgnored.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentFieldSvnMultiChoice.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentFieldSvnSchedule.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentFieldSvnTextStatus.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentInstance.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentInstanceBoolean.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentInstanceMultiChoice.h
# End Source File
# Begin Source File

SOURCE=.\include\ContentInstanceString.h
# End Source File
# Begin Source File

SOURCE=..\totalcmd\include\contentplug.h
# End Source File
# Begin Source File

SOURCE=.\include\FieldLoader.h
# End Source File
# Begin Source File

SOURCE=.\include\MultiChoiceDef.h
# End Source File
# Begin Source File

SOURCE=.\include\MultiChoiceDefSchedule.h
# End Source File
# Begin Source File

SOURCE=.\include\MultiChoiceDefStatus.h
# End Source File
# Begin Source File

SOURCE=.\include\SmartPtr.h
# End Source File
# Begin Source File

SOURCE=.\include\svn_wcprops.h
# End Source File
# Begin Source File

SOURCE=.\include\SvnEx.h
# End Source File
# Begin Source File

SOURCE=.\include\SvnFieldLoader.h
# End Source File
# Begin Source File

SOURCE=.\SvnFieldLoader__EntryCache.h
# End Source File
# Begin Source File

SOURCE=.\include\SvnPool.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
