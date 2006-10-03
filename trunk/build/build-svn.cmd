@echo off

call svn.cmd %wc_dir_apr% %rep_url_apr%
if defined build_errorlevel goto error
call svn.cmd %wc_dir_apu% %rep_url_apu%
if defined build_errorlevel goto error
call svn.cmd %wc_dir_api% %rep_url_api%
if defined build_errorlevel goto error
call svn.cmd %wc_dir_svn% %rep_url_svn%
if defined build_errorlevel goto error
call svn.cmd %wc_dir_neon% %rep_url_neon%
if defined build_errorlevel goto error


call "%exec_msdev_env%"
if errorlevel 1 (
  echo Could not execute Visual Studio build environment.
  echo Build environment file was %exec_msdev_env%
  goto error
)

rem +++ enter svn dir +++
pushd %wc_dir_svn%
gen-make.py %svn_gen_make_opts%
if errorlevel 1 (
  set build_errorlevel=%ERRORLEVEL%
  echo Subversion configure failed.
  echo Option string was %svn_gen_make_opts%
  popd
  goto error
)

msdev "subversion_msvc.dsw" /MAKE "__LIBS__ - Win32 Release"
if errorlevel 1 (
  set build_errorlevel=%ERRORLEVEL%
  echo Subversion Build failed.
  popd
  goto error
)

popd
rem +++ left svn dir +++

call collect-files.cmd
if defined build_errorlevel goto error

:error
:end
