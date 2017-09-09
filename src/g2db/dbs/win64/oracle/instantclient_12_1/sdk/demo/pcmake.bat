@echo off
Rem #
Rem # pcmake.bat
Rem #
Rem #  Copyright (c) Oracle Corporation 2000, 2008. All Rights Reserved.
Rem #
Rem #    NAME
Rem #      pcmake.bat - batch file for building PRO*C demos. 
Rem #
Rem #    DESCRIPTION
Rem #      Using this batch file to build PRO*C demos,
Rem #      e.g.  To build procdemo, 
Rem #            At command prompt where procdemo.pc is located, 
Rem #            type: % pcmake procdemo
Rem #     
Rem #      The purpose of this batch file is to illustrate how PRO*C
Rem #      applications can be built at the command prompt.  In order to
Rem #      use this batch file, installation of Microsoft Visual Studio 
Rem #      is required.   PRO*C command line options and linker options
Rem #      vary depending on your application.   This batch file
Rem #      is just an example for your reference.
Rem #
Rem #      For environment setup, please read the note below.
Rem #
Rem #    NOTES
Rem #       Environment variables must be set before using this batch file.
Rem #       They are as follows:
Rem #       1. VCINSTALLDIR     : This variable is defined by running a batch
Rem #                        file, vcvars32.bat, in Microsoft Visual Studio 
Rem #                        directory. You can find it using Windows Explorer.
Rem #

Rem # Please set this variable to your instant client installation directory.
set ICHOME=..\..

Rem Environment Check:
if ("%VCINSTALLDIR%") == ("") goto vcinstalldir_error

Rem -------------------------------------
Rem INSTANT CLIENT DIRECTORY PATHS
Rem -------------------------------------
set ICINCHOME=%ICHOME%\sdk\include
set ICLIBHOME=%ICHOME%\sdk\lib\msvc
set PCSCFG=%ICHOME%\precomp\admin\pcscfg.cfg
set PROC=%ICHOME%\sdk\proc.exe
Rem -------------------------------------

set SQLLIB_lib=orasql12.lib

set pcfile=%1

if (%pcfile%) == () goto usage

@echo on
echo %pcfile%
%PROC% parse=full iname=%pcfile%.pc config="%PCSCFG%" include="%ICINCHOME%" include="." include="%VCINSTALLDIR%\include" include="%VCINSTALLDIR%\PlatformSDK\include"
@echo off
goto clink


:clink
cl -I%ICINCHOME% -I. -I"%VCINSTALLDIR%\include" -I"%VCINSTALLDIR%\PlatformSDK\include" -D_DLL -D_MT %1.c /link /LIBPATH:%ICLIBHOME% %SQLLIB_lib% oci.lib kernel32.lib msvcrt.lib /nod:libc
goto end


:usage
echo .
echo usage pcmake filename.pc [ i.e. pcmake procdemo ]
echo .
goto end


:vcinstalldir_error 
echo .
echo Environment variable VCINSTALLDIR must be set before running this batch file.
echo Please run vcvars32.bat from MS Visual Studio directory.
echo .
goto end

:end
