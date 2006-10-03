@echo off

echo svn_wcprops working copy is %base_dir%
echo.

if defined skip_svn (
  echo Subversion operations are not performed.
) else (
  echo Subversion operations are performed, repository URLs:
  echo APR:        %rep_url_apr%
  echo APR-Util:   %rep_url_apu%
  echo APR-Iconv:  %rep_url_api%
  echo Subversion: %rep_url_svn%
  echo Neon:       %rep_url_neon%
)
echo.

echo Library Working copy paths:
echo APR:        %wc_dir_apr%
echo APR-Util:   %wc_dir_apu%
echo APR-Iconv:  %wc_dir_api%
echo Subversion: %wc_dir_svn%
echo Neon:       %wc_dir_neon%
echo ZLib:       %zlib_dir%
echo.

echo Binaries to be used:
echo MSVC Environment: %exec_msdev_env%
if not defined skip_svn echo Subversion:       %exec_svn%
