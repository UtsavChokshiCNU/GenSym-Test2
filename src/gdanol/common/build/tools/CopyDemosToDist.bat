echo off
REM *** Setup variables ***
REM
REM  Arguments
REM	SRCDIR  The sandbox where the sources reside
REM	TARGDIR  The base directory for the dev & dist files
REM	VERCYC  The version cycle code for the dist files
REM
echo "** Starting to copy executables & demos **"

set SRCDIR=%1
set TARGDIR=%2
set GDAVERCYC=%3
set NOLVERCYC=%4

echo SRCDIR = %SRCDIR%
echo TARGDIR = %TARGDIR%
echo GDAVERCYC = %GDAVERCYC%
echo NOLVERCYC = %NOLVERCYC%

set BUILD=%SRCDIR%\gdanol\common\build
set GBIN=%SRCDIR%\gdanol\gda\bin
set NBIN=%SRCDIR%\gdanol\nol\bin
set DEMOS=%SRCDIR%\gdanol\common\demos\kbs
set FILEX=%SRCDIR%\gdanol\common\build\tools\filex.txt
set GDIST=%TARGDIR%\gda\dist\%GDAVERCYC%
set NDIST=%TARGDIR%\nol\dist\%NOLVERCYC%

echo BUILD = %BUILD%
echo GBIN = %GBIN%
echo NBIN = %NBIN%
echo DEMOS = %DEMOS%
echo FILEX = %FILEX%
echo GDIST = %GDIST%
echo NDIST = %NDIST%

REM *** Cleanup ~ files ***
echo "** Cleaning up files **"
del /Q %GDIST%\kbs\*.kb~
del /Q %NDIST%\kbs\*.kb~

REM *** Copy GDA files to target directories ***
echo "** Copying GDA files to target directories **"
copy %BUILD%\README %GDIST%
copy /B %GBIN%\gdasound.exe %GDIST%\bin
mkdir %GDIST%\examples
copy /B %DEMOS%\gdacerel.kb %GDIST%\examples
copy /B %DEMOS%\gdareact.kb %GDIST%\examples
copy /B %DEMOS%\gdatank.kb %GDIST%\examples

:NCOPY

REM *** Copy NOL files to target directories ***
echo "** Copying NOL files to target directories **"
copy /B %NBIN%\ntnol.exe %NDIST%\bin
copy /B %NBIN%\alphanol %NDIST%\bin
copy /B %NBIN%\hp700nol %NDIST%\bin
copy /B %NBIN%\rs6nol %NDIST%\bin
copy /B %NBIN%\solnol %NDIST%\bin
copy %DEMOS%\bakery-demo\*.* %NDIST%\bakery-demo\*.*
copy %DEMOS%\bleach-demo\*.* %NDIST%\bleach-demo\*.*
copy %DEMOS%\total-demo\*.* %NDIST%\total-demo\*.*

echo "** Finished copying the GDA & NOL files to targets **"
