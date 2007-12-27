@echo off

call svn.cmd %wc_dir_apr% %rep_url_apr%
if defined build_errorlevel goto error
call svn.cmd %wc_dir_apu% %rep_url_apu%
if defined build_errorlevel goto error
call svn.cmd %wc_dir_api% %rep_url_api%
if defined build_errorlevel goto error
call svn.cmd %wc_dir_svn% %rep_url_svn%
if defined build_errorlevel goto error
if defined %wc_dir_neon% (
  call svn.cmd %wc_dir_neon% %rep_url_neon%
) else (
  call :fetch_neon
)
if defined build_errorlevel goto error


call :fetch_zlib
if defined build_errorlevel goto error


call "%exec_msdev_env%"
if errorlevel 1 (
  set build_errorlevel=%ERRORLEVEL%
  echo Could not execute Visual Studio build environment.
  echo Build environment file was %exec_msdev_env%
  goto error
)

rem +++ enter svn dir +++

if not exist "%wc_dir_svn%" (
  echo Creating Subversion working copy %wc_dir_svn%
  md "%wc_dir_svn%"
  if errorlevel 1 (
    set build_errorlevel=%ERRORLEVEL%
    echo Subversion working copy could not be created.
    goto error
  )
)

pushd "%wc_dir_svn%"
if errorlevel 1 (
  set build_errorlevel=%ERRORLEVEL%
  echo Subversion working copy directory does not exist.
  echo Subversion working copy directory is %wc_dir_svn%
  goto error
)

python gen-make.py %svn_gen_make_opts%
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

goto end
rem ### END main ###

:fetch_neon
if not exist "%wc_dir_neon%" (
  echo Creating neon directory %wc_dir_neon%
  md "%wc_dir_neon%"
  if errorlevel 1 (
    set build_errorlevel=%ERRORLEVEL%
	echo Could not create neon directory %wc_dir_neon%
    goto error
  )
)

pushd "%wc_dir_neon%"
if errorlevel 1 (
  set build_errorlevel=%ERRORLEVEL%
  echo Could not change into neon directory %wc_dir_neon%
  goto error
)

if not exist .version (
  if not exist "neon-%neon_version%.tar.gz" (
    "%build_dir%\wget.exe" http://www.webdav.org/neon/neon-%neon_version%.tar.gz
    if errorlevel 1 (
      set build_errorlevel=%ERRORLEVEL%
      echo Could not download neon source tarball from http://www.webdav.org/neon/neon-%neon_version%.tar.gz
      popd
      goto error
    )
  )

  "%build_dir%\gunzip.exe" -c neon-%neon_version%.tar.gz > neon-%neon_version%.tar
  if errorlevel 1 (
    set build_errorlevel=%ERRORLEVEL%
    echo Could not inflate neon from neon-%neon_version%.tar.gz
    popd
    goto error
  )

  "%build_dir%\tar.exe" xf neon-%neon_version%.tar
  if errorlevel 1 (
    set build_errorlevel=%ERRORLEVEL%
    echo Could not unpack neon from neon-%neon_version%.tar
    del /Q neon-%neon_version%.tar > nul
    popd
    goto error
  ) 
  del /Q neon-%neon_version%.tar > nul

  for /D %%i in (neon-%neon_version%\*.*) do (
    move "%%~fi" "%wc_dir_neon%\."
    if errorlevel 1 (
      set build_errorlevel=%ERRORLEVEL%
      echo Could not move %%~fi to %wc_dir_neon%
      popd
      goto error
    ) 
  )
  
  move "neon-%neon_version%\*.*" "%wc_dir_neon%\."
  if errorlevel 1 (
    set build_errorlevel=%ERRORLEVEL%
    echo Could not move neon to %wc_dir_neon%
    popd
    goto error
  )

  rmdir neon-%neon_version%
  if errorlevel 1 (
    set build_errorlevel=%ERRORLEVEL%
    echo Could not delete %wc_dir_neon%\neon-%neon_version%
    popd
    goto error
  )
)

popd
goto end
rem ### END fetch_neon ###


:fetch_zlib
if not exist "%zlib_dir%" (
  echo Creating zlib directory %zlib_dir%
  md "%zlib_dir%"
  if errorlevel 1 (
    set build_errorlevel=%ERRORLEVEL%
    goto error
  )
)

pushd "%zlib_dir%"
if errorlevel 1 (
  set build_errorlevel=%ERRORLEVEL%
  echo Could not change into zlib directory %zlib_dir%
  goto error
)

if not exist zlib.h (
  if not exist zlib123.zip (
    wget http://www.zlib.net/zlib123.zip
    if errorlevel 1 (
      set build_errorlevel=%ERRORLEVEL%
      echo Could not download zlib from http://www.zlib.net/zlib123.zip
      popd
      goto error
    )
  )

  if not exist zlib.h (
    "%build_dir%\unzip.exe" zlib123.zip
    if errorlevel 1 (
      set build_errorlevel=%ERRORLEVEL%
      echo Could not unpack zlib from zlib123.zip
      popd
      goto error
    )
  )
)
popd
goto end
rem ### END fetch_zlib ###


:error
:end
