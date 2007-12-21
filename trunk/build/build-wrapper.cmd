@echo off

setlocal
set build_dir=%~dp1\build
pushd "%build_dir%"

call import-conf.cmd "%~dp1"
if defined build_errorlevel goto error

call "%~f2"
if defined build_errorlevel goto error

echo Build completed.
goto end

:error
echo An error occurred (%build_errorlevel%). Please check %conf_file%
echo and tweak your settings.
echo Your settings follow:
echo.
call print-conf.cmd

:end
popd
endlocal
