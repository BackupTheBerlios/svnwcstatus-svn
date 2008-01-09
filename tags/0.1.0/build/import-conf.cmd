@echo off

set base_dir=%~f1
set conf_file=%base_dir%build-conf.cmd

if not exist "%conf_file%" (
  call :create_conf "build-conf.tmpl"
  if defined build_errorlevel goto end
) else (
  call :exec_conf
  if defined build_errorlevel goto end
)

goto end


rem ###########################################################################
:create_conf
copy "%~f1" "%conf_file%" > nul
if errorlevel 1 (
  echo Template file %~f1 could not be copied to %conf_file%.
  goto error
)

echo It seems to be the first time that you run this build script. A default options
echo file has been created: %conf_file%
echo.
echo An editor is now started so that you can edit the default settings.

start /wait notepad "%conf_file%"
pause
call :exec_conf
if defined build_errorlevel goto end
call print-conf.cmd
pause
goto end

rem ###########################################################################
:exec_conf
call %conf_file%
if errorlevel 1 (
  echo Could not execute build configuration file.
  echo File is %conf_file%
  goto error
) else echo Configuraton has been successfully read from %conf_file%
goto end

rem ###########################################################################
:check_conf
if not defined skip_svn (
  call :check_exec exec_svn "%exec_svn%"
  if defined build_errorlevel goto end
)
call :check_exec exec_msdev_env "%exec_msdev_env%"
if defined build_errorlevel goto end
goto end

rem ###########################################################################
:check_exec
if not exist "%~f2" (
  call :search_in_path %1 "%~nx2"
)
goto end

rem ###########################################################################
:search_in_path
set __temp__=%~$PATH:2
if exist "%__temp__%" (
  set %1=%__temp__%
  set __temp__=
) else (
  set __temp__=
  echo %~2 not found.
  goto error
)
goto end

:error
set build_errorlevel=%ERRORLEVEL%

:end
