@echo off

if "%OS%"=="Windows_NT" setlocal
if "%OS%"=="WINNT" setlocal

set conf_file=configure-svn.props.bat
set conf_file_tmpl=configure-svn.props.tmpl

if not exist "%conf_file%" (
  copy "%conf_file_tmpl%" "%conf_file%" > nul
  if errorlevel 1 (
    echo Template file %conf_file_tmpl% could not be copied.
    goto end
  )
)

call %conf_file%

if exist "%svn_home%\build\win32\msvc-dsp" (
  echo Subversion already configured for MSVC. If you don't want to
  echo change this configuration, now is the time to hit Ctrl + C.
  pause
  echo.
)

if not exist "%svn_home%\gen-make.py" (
  echo Subversion not found in %svn_home%.
  goto env_error
)

if not exist "%apr_home%\apr.dsp" (
  echo apr not found in %apr_home%.
  goto env_error
)

if not exist "%apu_home%\aprutil.dsp" (
  echo apr-util not found in %apu_home%.
  goto env_error
)

if not exist "%api_home%\apriconv.dsp" (
  echo apr-iconv not found in %api_home%.
  goto env_error
)

if not exist "%neon_home%\neon.dsp" (
  echo Neon not found in %neon_home%.
  goto env_error
)

set svn_gen_make_opts=-t dsp --release --with-apr="%apr_home%" --with-apr-util="%apu_home%" --with-apr-iconv="%api_home%" --with-neon="%neon_home%"

echo Configuring Subversion in %svn_home% with following options:
echo %svn_gen_make_opts%
echo.
pause

echo.
pushd "%svn_home%"
call "gen-make.py" %svn_gen_make_opts%
popd

echo.
if errorlevel 1 (
  echo Error configuring Subversion.
) else (
  echo Subversion successfully configured.
)

goto end
:env_error
echo Please check the environment defined in %conf_file%.

:end

if "%OS%"=="Windows_NT" endlocal
if "%OS%"=="WINNT" endlocal

pause
