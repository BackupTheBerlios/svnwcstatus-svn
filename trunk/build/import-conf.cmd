@echo off

set base_dir=%~f1
set conf_file=%base_dir%build-conf.cmd

setlocal

set conf_file_tmpl=build-conf.tmpl

if not exist "%conf_file%" (
  copy "%conf_file_tmpl%" "%conf_file%" > nul
  if errorlevel 1 (
    echo Template file %conf_file_tmpl% could not be copied to %conf_file%.
    endlocal
    goto error
  )
)

endlocal

call %conf_file%
if errorlevel 1 (
  echo Could not execute build configuration file.
  echo File is %conf_file%
  goto error
)

call :check_conf exec_svn "%exec_svn%"
if defined build_errorlevel goto end
call :check_conf exec_msdev_env "%exec_msdev_env%"
if defined build_errorlevel goto end

goto end

:check_conf
if not exist "%~f2" (
  call :search_in_path %1 "%~nx2"
)
goto end

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
