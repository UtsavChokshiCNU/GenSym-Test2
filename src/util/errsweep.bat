@echo off
rem # Usage: errsweep { -init | -finish | <filename> }
rem #   options:
rem #     -init:   remove errors.log, current.bat and any file referenced by it
rem #     -finish: add contents of current.bat to errors.log and remove it
rem #     <filename>:  see description below
rem #
rem #   This script monitors errors encountered during makefile target creation
rem # and removes potentially malformed files.  The script proceeds in two
rem # stages.  As each target in the makefile is processed, the target is
rem #  "registered" by calling this script, which stores its name, <filename>,
rem # in current.bat in the current directory.  To allow the filename to be
rem # read, it is stored as a line to set an environment variable, filename.
rem # When target creation is complete, the makefile removes current.bat.
rem # If target creation fails, current.bat is not removed, thereby indicating
rem # an error in target creation.
rem #   This script first checks for previous errors by looking for current.bat,
rem # and if found, adds the file named in it to errors.log and deletes
rem # current.bat.  errors.log provides a convenient list of files that
rem # had creation errors.
rem #   A makefile should call errsweep -init initially and errsweep -finish
rem # just before completion.

if not "%1" == "" goto goodargs
    echo error: usage: errsweep "-init | -finish | <filename>"
    exit
:goodargs

rem # The call to current.bat sets variable %filename%
if not exist current.bat goto noclog
    call current.bat
    del current.bat
    echo %filename% >> errors.log
    if exist %filename% del %filename%
:noclog

if not "%1" == "-init" goto notinit
    if exist errors.log del errors.log
    exit
:notinit

rem # Store the parameter as the new filename.
if not "%1" == "-finish" echo set filename=%1 > current.bat
