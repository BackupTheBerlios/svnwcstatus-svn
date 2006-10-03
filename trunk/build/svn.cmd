@echo off

if defined skip_svn goto end

setlocal

set wc_dir=%~f1
set svn_url=%2

if exist "%wc_dir%\.svn" (
  echo Update of working copy %wc_dir%
  set svn_cmd=up
) else (
  echo Checking out %svn_url%
  set svn_cmd=co %svn_url%
)

set cmdline=%exec_svn% %svn_cmd% "%wc_dir%"
%cmdline%
if errorlevel 1 (
  echo Subversion command failed:
  echo %cmdline%
  goto error
)

endlocal
goto end

:error
endlocal
set build_errorlevel=%ERRORLEVEL%

:end
