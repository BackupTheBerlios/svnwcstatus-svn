@echo off

rem ### HEADERS ###
call :collect_files %wc_dir_apr%\include %lib_dir%\include\apr *.* /S
if defined build_errorlevel goto end_after_error
call :collect_files %wc_dir_apu%\include %lib_dir%\include\apr-util *.* /S
if defined build_errorlevel goto end_after_error
call :collect_files %wc_dir_api%\include %lib_dir%\include\apr-iconv *.* /S
if defined build_errorlevel goto end_after_error *.lib
call :collect_files %wc_dir_svn%\subversion\include %lib_dir%\include *.*
if defined build_errorlevel goto end_after_error


rem ### LIBRARIES ###
call :collect_files %wc_dir_apr%\Release %lib_dir%\lib\apr *.lib
if defined build_errorlevel goto end_after_error
call :collect_files %wc_dir_apu%\Release %lib_dir%\lib\apr-util *.lib
if defined build_errorlevel goto end_after_error
call :collect_files %wc_dir_apu%\xml\expat\lib\LibR %lib_dir%\lib\apr-util *.lib
if defined build_errorlevel goto end_after_error
call :collect_files %wc_dir_api%\Release %lib_dir%\lib\apr-iconv *.lib
if defined build_errorlevel goto end_after_error
call :collect_svn_libs
if defined build_errorlevel goto end_after_error
call :collect_files %zlib_dir% %lib_dir%\lib zlibstat.lib
if defined build_errorlevel goto end_after_error


rem ### BINARIES ###
call :collect_files %wc_dir_apr%\Release %lib_dir%\bin *.dll
if defined build_errorlevel goto end_after_error
call :collect_files %wc_dir_apu%\Release %lib_dir%\bin *.dll
if defined build_errorlevel goto end_after_error
call :collect_files %wc_dir_api%\Release %lib_dir%\bin *.dll
if defined build_errorlevel goto end_after_error
call :collect_files %wc_dir_api%\Release\iconv %lib_dir%\bin\iconv *.so /S
if defined build_errorlevel goto end_after_error


goto end


:collect_svn_libs
for /D %%i in (%wc_dir_svn%\Release\subversion\libsvn_*) do (
  call :collect_files %%i %lib_dir%\lib *.lib
  if defined build_errorlevel goto end_after_error
)
goto end_after_error

:collect_files
setlocal
set cmdline=xcopy "%~f1\%3" "%~f2" /Q /I /Y %4
%cmdline%
if errorlevel 1 (
  echo Error copying files: %cmdline%
  endlocal
  set build_errorlevel=%ERRORLEVEL%
  goto end_after_error
)
endlocal
goto end_after_error

:end
:end_after_error
