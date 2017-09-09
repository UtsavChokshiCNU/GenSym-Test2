@echo off
setlocal

if not _%3==_ goto :good_args
echo Wait for timeout (approximate, in seconds) given in parameter 3.
echo Then kill the process where each of keys given by parameter 1 and 2 are
echo present in the command line
goto :end_of_file

:good_args

set /a i=1
set search_expr="CommandLine like '%%%~1%%' and CommandLine like '%%%~2%%' and not CommandLine like '%%KillProcessByKeyAfterTimeout%%' and not CommandLine like '%%wmic.exe process%%'"

:loop
  set "wmic_cmd=WMIC.exe process where %search_expr% get CommandLine 2> nul | findstr %1" 
  %wmic_cmd% > nul 2> nul
  if errorlevel 1 goto :end_of_file
  REM Sleep for a short time
  REM Using ping is a "canonical way" to sleep in batch file on Windows
  REM Next command will sleep for approximately n-1 or n seconds, depending on if 127.0.0.1 is reachable or not
  ping 127.0.0.1 -n 3 -w 10 >nul
  set /a i = %i% + 1
if not _%i%==_%3 goto :loop

echo "%0: about to request process to terminate, where command line containing key %1"

REM Following file writes are specially for regression test suite
REM In ideal world where we would keep modularity, %3 would be a name of 
REM batch file to call, before-kill-callback, but let us make it work at first
set backtrace_file=c:\g2\src\tests\results\%1\startlw1mptimeout-pseudo-backtrace.txt
echo "%0: about to request process to terminate, where command line containing key %1" > %backtrace_file%
set rg_file=c:\g2\src\tests\results\%1\startlw1mptimeout.rg
echo %1, Pseudo-test file created by %0 to inform that LW G2 instance timed out> %rg_file%
echo.>>%rg_file%
echo NO-TIMEOUT-DETECTED-BY-STARTLW1MPTIMEOUT-PSEUDO-TEST,FAILED>> %rg_file%
echo.>>%rg_file%
echo We have extra lines for format compatibility with G2-generated *.rg files >>%rg_file%
echo ------->>%rg_file%

echo Executing command and gathering its stdout and stderr: >%backtrace_file% 
echo WMIC.exe process where %search_expr% call terminate(0) >>%backtrace_file% 
echo ------- output follows ------------------- >>%backtrace_file% 
WMIC.exe process where %search_expr% call terminate(0) >>%backtrace_file% 2>&1

:end_of_file
