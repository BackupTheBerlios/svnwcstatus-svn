@echo off

for %%I in (svn_wcstatus\*.cpp) do (
  copy "%%~dpfI" "%%~dpfI.bak"
  type D:\Eclipse\Workspace\svn_wcstatus\lic.txt > "%%~dpfI"
  type "%%~dpfI.bak" >> "%%~dpfI"
  del ""%%~dpfI.bak"
)
for %%I in (svn_wcstatus\include\*.h) do (
  copy "%%~dpfI" "%%~dpfI.bak"
  type D:\Eclipse\Workspace\svn_wcstatus\lic.txt > "%%~dpfI"
  type "%%~dpfI.bak" >> "%%~dpfI"
  del ""%%~dpfI.bak"
)
