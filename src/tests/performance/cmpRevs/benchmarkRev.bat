REM %1 is the SVN revision number
REM %2 is the use-case code
cd ../src
@REM If authentication fails, use gdevqa / t7vuAwxT
svn revert . -R
svn update -r %1
cd tests/performance
REM We had inconsistent measurements prior to that revision
svn update ss-function-benchmark-kb -r 85391
call build.bat
call run-performance-tests.bat %1 %2