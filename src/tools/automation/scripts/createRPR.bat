@echo off

set INITDIR=%CD%
set G2=c:\g2\src
set STDREV=%1
set ENTREV=%2
set RPRDIR=%INITDIR%\RPR
set STDDIR=%RPRDIR%\STANDARD_%1
set ENTDIR=%RPRDIR%\ENTERPRISE_%2



IF EXIST %RPRDIR% (
RD /S /Q %RPRDIR%
) 


md %RPRDIR%
md %STDDIR%
md %ENTDIR%

echo Cleaning up %G2%
call svn cleanup %G2%
echo Reverting any local changes %G2%
call svn revert %G2% -R
echo Updating source tree %G2%
call svn update --username gdevqa --password t7vuAwxT -r %STDREV% %G2%
cd %G2%\ant
echo Building standard version using ant
call ant build_32_std
cd %G2%\tests\performance\
echo Running performance tests
call run-performance-tests.bat 
echo Saving artifacts
COPY %G2%\tests\performance\results\*.txt %STDDIR%
del %G2%\tests\performance\results\*.txt

echo Cleaning up %G2%
call svn cleanup %G2%
echo Reverting any local changes %G2%
call svn revert %G2% -R
echo Updating source tree %G2%
call svn update --username gdevqa --password t7vuAwxT -r %ENTREV% %G2%
cd %G2%\ant
echo Building enterprise version using ant
call ant build_64_ent
cd %G2%\tests\performance\
echo Running performance tests
call run-performance-tests.bat 
echo Saving artifacts
COPY %G2%\tests\performance\results\*.txt %ENTDIR%
del %G2%\tests\performance\results\*.txt

ECHO Benchmark reports are generated
