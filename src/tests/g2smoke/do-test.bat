@echo off

rem # This batch file mimics the Unix shell script do-test, which contains
rem # extensive comments.

rem # -----------------------------------------------------------------
rem # Set default values for command-line arguments.  Note that even though
rem # DISPLAY may be set, it is not used.

set G2=.\g2.exe
set OK=.\g2v5.ok
set DISPLAY=0.0
set MODPATH=%SRCBOX%\kbs

set SMOKE_SOURCES=%SRCBOX%\tests\g2smoke
set SMOKE_ERROR=false

rem # -----------------------------------------------------------------
rem # Process command-line arguments.

:parse_loop
if "%1" == "" goto got_args

if NOT "%1" == "-g2" goto next1
      set G2=%2
      goto got1
:next1
   if NOT "%1" == "-ok" goto next2
      set OK= %2
      goto got1
:next2
   if NOT "%1" == "-display" goto next3
      set DISPLAY=%2
      goto got1
:next3
   if NOT "%1" == "-modpath" goto default
      set MODPATH=%2
      goto got1
:default
   echo Invalid switch: %1
   goto usage
:got1
   shift
   shift
   goto parse_loop

:got_args
rem # -----------------------------------------------------------------
rem # Set default directory to g2 test directory, verify that the g2 image is
rem # available, and get a copy of smoke1.kb.
rem # Bug: "echo. creates a file with a blank line, not an empty file.

cd %DSTBOX%\g2\test

if exist %G2% goto else1
    echo smoke test error: no g2 image found
    set SMOKE_ERROR=true
    goto finalstatus
:else1
    copy %SMOKE_SOURCES%\smoke1.kb .

rem # -----------------------------------------------------------------
rem # Run g2 with smoke1.kb and redirect output to a temporary file.
rem # When g2 completes, store any unexpected lines in smoke.out so
rem # that they will cause the "checkoutput" comparison below to fail.
rem # Echo the g2 output for users to see. Finally, check for existence of
rem # smoke2.kb, which should have been saved

echo LOG: running g2 with smoke1.kb

%G2% -module_search_path %MODPATH% -ok %OK% -kb smoke1.kb -start > %tmp%\12345.tmp

find /i "error" < %tmp%\12345.tmp >> smoke.out

type %tmp%\12345.tmp

if exist smoke2.kb goto skip1
    echo smoke test error: smoke1.kb failed to write smoke2.kb
    set SMOKE_ERROR=true
    goto finalstatus

:skip1
rem # -----------------------------------------------------------------
rem # Run g2 with smoke2.kb and proceed as above for smoke1.kb.

echo LOG: running g2 with smoke2.kb

%G2% -module_search_path %MODPATH% -ok %OK% -kb smoke2.kb -start > %tmp%\12345.tmp
 
find /i "error" < %tmp%\12345.tmp  >> smoke.out
 
type %tmp%\12345.tmp 

rem # -----------------------------------------------------------------
rem # Check whether the test was successful by comparing what g2 wrote
rem # with expected output.  Print an appropriate status message.
rem # We assume that the fc command returns an errorlevel of 1 if there are
rem # differences.
rem # Bug: fc does not appear to set errorlevel.  It is also
rem # very chatty about what it's doing.

fc smoke.out %SMOKE_SOURCES%\expected.out

if errorlevel 1 set SMOKE_ERROR=true

:finalstatus
rem # -----------------------------------------------------------------
rem # Check whether the test was successful by comparing what g2 wrote
rem # with expected output.  Print an appropriate status message.

if %SMOKE_ERROR%==true goto failed
   echo Smoke Test Passed.
   goto theend
:failed
   echo Smoke Test Failed.

goto theend

:usage
echo usage: [-g2 g2-image] [-ok ok-file]

:theend
rem # -----------------------------------------------------------------
rem # Do some cleanup.

if exist smoke1.kb del /f smoke1.kb
if exist smoke2.kb del /f smoke2.kb
if exist smoke.out del /f smoke.out
if exist %tmp%\12345.tmp del /f %tmp%\12345.tmp
set G2=
set OK=
set DISPLAY=
set MODPATH=
set SMOKE_SOURCES=
set SMOKE_ERROR=
