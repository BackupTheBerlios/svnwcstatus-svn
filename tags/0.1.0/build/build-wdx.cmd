@echo off

call "%exec_msdev_env%"
if errorlevel 1 (
  set build_errorlevel=%ERRORLEVEL%
  echo Could not execute Visual Studio build environment.
  echo Build environment file was %exec_msdev_env%
  goto error
)

rem ### enter svn_wcstatus dir ###

pushd "%base_dir%"
if errorlevel 1 (
  set build_errorlevel=%ERRORLEVEL%
  echo Could not change into svn_wcstatus directory
  echo svn_wcstatus directory is %base_dir%
  goto error
)

msdev "svn_wcstatus.dsw" /MAKE "svn_wcstatus - Win32 Release"
if errorlevel 1 (
  set build_errorlevel=%ERRORLEVEL%
  echo svn_wcstatus build failed
  popd
  goto error
)

popd
rem ### left svn_wcstatus dir ###


:error
:end
