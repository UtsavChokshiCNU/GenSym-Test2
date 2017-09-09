@echo off
rem %1 - a lisp file to load in order to start lisp-unit tests
rem %2 - a folder where LispWork build script is located
rem %3 - a lisp to run tests against (see labels below) 
rem %4 - to run coverage test, pass the word coverage 

setlocal

if "%4"=="coverage" goto this_is_coverage

set G2_UNIT_TESTS_CALCULATE_COVERAGE=
set result_folder=..\..\..\results\api-tests\lisp

goto endif_coverage
:this_is_coverage

set G2_UNIT_TESTS_CALCULATE_COVERAGE=yes
set result_folder=..\..\..\results\coverage\lisp

:endif_coverage


if not exist %result_folder% md %result_folder%

rem Build Console LispWorks if absent
rem pushd %2
rem call build
rem popd

rem Delete obselete FASLs
call del-fasls

if not "%3"=="" (goto %3) else (goto lw64)

:symscale
lw64-console -load run-tests-symscale.lisp >%result_folder%\symscale.log
if not "%3"=="" goto end

:lw64
lw64-console -load %1 >%result_folder%\lw64.log
if not "%3"=="" goto end

rem :lw
rem lw-console -load %1 >%result_folder%\lw.log
rem if not "%3"=="" goto end

:ccl64
wx86cl64 --load %1 >%result_folder%\ccl64.log 2>&1
if not "%3"=="" goto end

:sbcl64
sbcl-x64 --disable-debugger --load %1 >%result_folder%\sbcl64.log 2>&1
if not "%3"=="" goto end

rem 32-bit SBCL and CCL are believed to fail, so there are no branches for them

:end
echo Lisp-unit tests finished!
