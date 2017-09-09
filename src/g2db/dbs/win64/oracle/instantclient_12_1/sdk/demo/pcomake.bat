@echo off
Rem #
Rem # pcomake.bat
Rem #
Rem #  Copyright (c) Oracle Corporation 2000, 2008. All Rights Reserved.
Rem #
Rem #    NAME
Rem #      pcomake.bat - Batch file for building Pro*COBOL demos. 
Rem #
Rem #    DESCRIPTION
Rem #      Using this batch file to build Pro*COBOL demos,
Rem #      e.g.  To build procobdemo, 
Rem #            At command prompt where procobdemo.pco is located, 
Rem #            type: % pcomake procobdemo
Rem #
Rem #      In general, to build any procob program
Rem #            At command prompt where <filename>.pco is located,
Rem #            type: % pcomake <filename>
Rem #     
Rem #      The purpose of this batch file is to illustrate how Pro*COBOL
Rem #      applications can be built at the command prompt in 
Rem #      Instant Client environment.  
Rem #

Rem # Please set this variable to your instant client installation directory.
set ICHOME=..\..

Rem -------------------------------------
Rem INSTANT CLIENT FILEPATHS
Rem -------------------------------------
set ICLIBHOME=%ICHOME%\sdk\lib\msvc
set PCBCFG=%ICHOME%\precomp\admin\pcbcfg.cfg
set PROCOB=%ICHOME%\sdk\procob.exe
Rem -------------------------------------

set SQLLIB_lib=orasql12.lib

set pcofile=%1

if (%pcofile%) == () goto usage

@ECHO ON
echo Precompiling %pcofile%.pco......
%PROCOB% iname=%pcofile%.pco config=%PCBCFG% ireclen=132
@ECHO OFF
goto do_compile

:do_compile
echo Compiling %pcofile%......
@ECHO ON
cobol %pcofile% /anim /litlink /ibmcomp /NESTCALL makesyn "COMP-5" = "COMP";
cbllink %pcofile% /M%pcofile% %ICLIBHOME%\%SQLLIB_lib%
@ECHO OFF
goto end

:usage
echo .
echo usage: pcomake filename [ Ex: pcomake procobdemo ]
echo .
goto end

:end
