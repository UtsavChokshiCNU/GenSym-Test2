@ECHO OFF
REM --------------------------------------------------------------------------------------------
REM File    : SetEnv.Bat
REM
REM Abstract: This batch file sets the appropriate environment
REM           variables for the Platform SDK build envionment with
REM           respect to OS and platform type.
REM
REM "Usage:    Setenv [/2000 | XP32 | /XP64 | /SRV32 | /SRV64 | /x86_64] [/DEBUG | /RETAIL]"
REM
REM                  /2000 - target Windows 2000 and IE 5.0
REM                  /XP32 (default) - target Windows XP 32
REM                  /XP64 - target Windows XP 64
REM                  /SRV32 - target Windows Server 2003 32 bit
REM                  /SRV64 - target Windows Server 2003 64 bit
REM                  /x86_64 - targe Windows for the x86_64 bit platform
REM                  /DEBUG - set the environment to DEBUG
REM                  /RETAIL - set the environment to RETAIL
REM 
REM --------------------------------------------------------------------------------------------


:Chk_MSSdk
REM Need to set the CPU here
set CPU=i386
IF "%1" == "/SRV64" set CPU=IA64
IF "%1" == "/XP64" set CPU=IA64
IF "%1" == "/x86_64" set CPU=AMD64

REM Check for PreRelease
IF "%1" == "/x86_64" set SDKPRERELEASE=1

REM Set the common env. variables
Goto Set_Common

:Chk_SetEnv
REM Verify that we have %MSSdk%\SetEnv.Bat
IF NOT EXIST "%MSSdk%\SetEnv.Bat" Goto ErrorBadPath

REM Check for the presence of MsVC5 or MsVC6.
goto Chk_MsVC

:Chk_OS
REM Set OS/platform-specific variables
goto Set_OS

:Finish
Goto end


REM -------------------------------------------------------------------
REM Set common variables
:Set_Common
REM -------------------------------------------------------------------
Set MSSdk=C:\Program Files\Microsoft SDK
Set Bkoffice=%MSSdk%\
Set Basemake=%MSSdk%\Include\BKOffice.Mak
Set INETSDK=%MSSdk%
Set MSSdk=%MSSdk%
Set Mstools=%MSSdk%

REM Default to DEBUG
goto set_DEBUG
:Done_Debug

REM Are we building DEBUG or RETAIL
if "%1" == "/RETAIL" goto set_RETAIL
if "%2" == "/RETAIL" goto set_RETAIL
if "%3" == "/RETAIL" goto set_RETAIL
if "%4" == "/RETAIL" goto set_RETAIL
:Done_Retail

goto Chk_SetEnv


REM -------------------------------------------------------------------
REM Set OS/platform-specific variables
:Set_OS
REM -------------------------------------------------------------------

IF "x%OS%x" == "xWindows_NTx" Goto Set_WinNT

REM Check to make sure we aren't attempting to open a 64bit build window
if "%1" == "/SRV64" goto ErrorUsage9x_IA64

Echo Setting SDK environment relative to %MSSdk%. 

REM check if the first parameter exists
if "%1"== "" goto Set_WinXP32
if "%1" == "/DEBUG" goto Set_2000
if "%1" == "/RETAIL" goto Set_2000
if "%1" == "/2000" goto Set_2000
if "%1" == "/cc" goto Set_2000
if "%1" == "/SRV32" goto Set_SRV32
if "%1" == "/XP32" goto Set_WinXP32

REM Usage not correct leave
goto ErrorUsage9x

REM -------------------------------------------------------------------
REM Set Windows 2000 specific variables
:Set_2000
REM -------------------------------------------------------------------
Echo Targeting Windows 2000 and IE 5.0 %DEBUGMSG%
Echo.
Set Lib=%MSSdk%\Lib;%Lib%
Set Include=%MSSdk%\Include;%Include%
Set Path="%MSSdk%\Bin;%MSSdk%\Bin\win95;%path%"
Set CPU=i386
set TARGETOS=WINNT
set APPVER=5.0
doskey > Nul
Goto Finish

REM -------------------------------------------------------------------
REM Set Windows XP32 specific variables
:Set_WinXP32
REM -------------------------------------------------------------------
Echo Targeting Windows WinXP32 %DEBUGMSG%
Echo.
Set Lib=%MSSdk%\Lib;%Lib%
Set Include=%MSSdk%\Include;%Include%
Set Path="%MSSdk%\Bin;%MSSdk%\Bin\win95;%path%"
Set CPU=i386
set TARGETOS=WINNT
set APPVER=5.01
doskey > Nul
Goto Finish


REM -------------------------------------------------------------------
REM Set Windows SRV32 specific variables
:Set_SRV32
REM -------------------------------------------------------------------
Echo Targeting Windows Server 2003 32bit %DEBUGMSG%
Echo.
Set Lib=%MSSdk%\Lib;%Lib%
Set Include=%MSSdk%\Include;%Include%
Set Path="%MSSdk%\Bin;%MSSdk%\Bin\win95;%path%"
Set CPU=i386
set TARGETOS=WINNT
set APPVER=5.02
doskey > Nul
Goto Finish


REM -------------------------------------------------------------------
REM Set Windows NT specific variables
:Set_WinNT
REM -------------------------------------------------------------------
IF /i "%PROCESSOR_ARCHITECTURE%" == "ALPHA" (Set CPU=ALPHA) else (Set CPU=i386)
IF "%1" == "/SRV64" SET CPU=IA64
IF "%1" == "/XP64" SET CPU=IA64
IF "%1" == "/x86_64" SET CPU=AMD64

REM Verify that we aren't building SRV64 on Windows NT Version 4.0
For /F "delims=;" %%i IN ('Cmd /c Ver') DO (
    IF "%%i"=="Windows NT Version 4.0  " (
        IF "%CPU%" == "IA64" goto ErrorUsage9x_IA64
        )
    )

REM check if the first parameter exists
if "%1"== "" goto Set2000_XP32
if "%1" == "/DEBUG" goto Set2000_2000
if "%1" == "/RETAIL" goto Set2000_2000
if "%1" == "/2000" goto Set2000_2000
if "%1" == "/cc" goto Set2000_2000
if "%1" == "/XP32" goto Set2000_XP32
if "%1" == "/XP64" goto Set2000_XP64
if "%1" == "/x86_64" goto Set2000_x86_64
if "%1" == "/SRV32" goto Set2000_SRV32
if "%1" == "/SRV64" goto Set2000_SRV64

REM Usage not correct leave
goto ErrorUsage


REM -------------------------------------------------------------------
REM Patch path to put Bin\WinNT\NT4 in path ahead of NT5 tools that don't run on NT4
:Set_WinNT_Cont
REM -------------------------------------------------------------------
REM Patch path to put Bin\WinNT\NT4 in path ahead of NT5 tools that don't run on NT4
For /F "delims=;" %%i IN ('Cmd /c Ver') DO (
    IF "%%i"=="Windows NT Version 4.0" (
        Set Path=%MSSdk%\Bin\WinNT\NT4;%Path%
        Goto Finish
        )
    )
Goto Finish

REM -------------------------------------------------------------------
REM Set Windows 2000 specific variables
:Set2000_2000
REM -------------------------------------------------------------------
Echo Targeting Windows 2000 and IE 5.0 %DEBUGMSG%
Echo.
Set Lib=%MSSdk%\Lib;%Lib%
Set Include=%MSSdk%\Include;%Include%
Set Path=%MSSdk%\Bin;%MSSdk%\Bin\WinNT;%path%
set APPVER=5.0
set TARGETOS=WINNT
Title Microsoft Platform SDK Windows 2000 IE 5.0 %DEBUGMSG% Build Environment
Goto Set_WinNT_Cont


REM -------------------------------------------------------------------
REM Set Windows XP32 specific variables
:Set2000_XP32
REM -------------------------------------------------------------------
Echo Targeting Windows XP 32 %DEBUGMSG%
Echo.
Set Lib=%MSSdk%\Lib;%Lib%
Set Include=%MSSdk%\Include;%Include%
Set Path=%MSSdk%\Bin;%MSSdk%\Bin\WinNT;%path%
set APPVER=5.01
set TARGETOS=WINNT
Title Microsoft Platform SDK Windows XP 32-bit IE 5.5 %DEBUGMSG% Build Environment
Goto Set_WinNT_Cont


REM -------------------------------------------------------------------
REM Set Windows XP 64 specific variables
:Set2000_XP64
REM -------------------------------------------------------------------
Echo Targeting Windows XP 64 %DEBUGMSG%
Echo.
Set Lib=%MSSdk%\Lib\IA64;%MSSdk%\Lib\IA64\mfc;
SET Include=%MSSdk%\Include;%MSSdk%\Include\Win64\crt;%MSSdk%\Include\Win64\crt\sys;%MSSdk%\Include\Win64\mfc;%MSSdk%\Include\Win64\atl;
Set Path=%MSSdk%\Bin\Win64;%MSSdk%\Bin;%MSSdk%\Bin\WinNT;%path%
set APPVER=5.01
set TARGETOS=WINNT
Title Microsoft Platform SDK Windows XP 64-bit IE 5.5 %DEBUGMSG% Build Environment
Goto Set_WinNT_Cont

REM -------------------------------------------------------------------
REM Set Windows Server 2003 32bit specific variables
:Set2000_SRV32
REM -------------------------------------------------------------------
Echo Targeting Windows Server 2003 32bit %DEBUGMSG%
Echo.
Set Lib=%MSSdk%\Lib;%Lib%
Set Include=%MSSdk%\Include;%Include%
Set Path=%MSSdk%\Bin;%MSSdk%\Bin\WinNT;%path%
set APPVER=5.02
set TARGETOS=WINNT
Title Microsoft Platform SDK Windows Server 2003 32-bit IE 6.0 %DEBUGMSG% Build Environment
Goto Set_WinNT_Cont


REM -------------------------------------------------------------------
REM Set Windows Server 2003 64-bit specific variables
:Set2000_SRV64
REM -------------------------------------------------------------------
Echo Targeting Windows Server 2003 64-bit %DEBUGMSG%
Echo.
Set Lib=%MSSdk%\Lib\IA64;%MSSdk%\Lib\IA64\mfc;
SET Include=%MSSdk%\Include\Win64\crt;%MSSdk%\Include\Win64\crt\sys;%MSSdk%\Include\Win64\mfc;%MSSdk%\Include\Win64\atl;%MSSdk%\Include;
Set Path=%MSSdk%\Bin\Win64;%MSSdk%\Bin;%MSSdk%\Bin\WinNT;%path%
set APPVER=5.02
set TARGETOS=WINNT
Title Microsoft Platform SDK Windows Server 2003 64-bit IE 6.0 %DEBUGMSG% Build Environment
Goto Set_WinNT_Cont

REM -------------------------------------------------------------------
REM Set Windows x86_64 specific variables
:Set2000_x86_64
REM -------------------------------------------------------------------
Echo Targeting Windows x86_64 %DEBUGMSG%
Echo.
Set Lib=%MSSdk%\Lib\x86-64;%MSSdk%\Lib\x86-64\mfc;
SET Include=%MSSdk%\Include\prerelease;%MSSdk%\Include\Win64\crt;%MSSdk%\Include\Win64\crt\sys;%MSSdk%\Include\Win64\mfc;%MSSdk%\Include\Win64\atl;%MSSdk%\Include;
Set Path=%MSSdk%\Bin\Win64\x86\x86-64;%MSSdk%\Bin;%MSSdk%\Bin\WinNT;%path%
set APPVER=5.02
set TARGETOS=WINNT
Title Microsoft Platform SDK x86_64-bit IE 6.0 %DEBUGMSG% Build Environment
Goto Set_WinNT_Cont

REM -------------------------------------------------------------------
:Chk_MsVC
REM -------------------------------------------------------------------
if "%CPU%" == "IA64" set MSVCVer=Win64
if "%CPU%" == "IA64" goto Chk_OS
if "%CPU%" == "AMD64" set MSVCVer=Win64
if "%CPU%" == "AMD64" goto Chk_OS
If "x%MSVCDir%x" == "xx" Goto NotMsVcDirExists
if "x%DevEnvDir%x" == "xx" Goto NotMsVnetDevDirExists
If "x%MSDevDir%x" == "xx" Goto NotMsDevDirExists

REM We have DevEnvDir and MSDevDir and MSVCDir (all are there - pick the one that was configured last)
IF NOT EXIST "%MSVCDir%\..\Common7\." goto VC6Detected
goto VC7Detected

REM -------------------------------------------------------------------
:NotMsVcDirExists
REM -------------------------------------------------------------------
REM MSVCDir does not exist, does DevEnvDir Exist?
IF "x%DevEnvDir%x" == "xx" Goto ChkVC6_MsVCDir

REM DevEnvDir Exists. Can We derive MSVCDir from it?
IF NOT EXIST "%DevEnvDir%\..\..\VC7\." goto ChkVC6_MsVCDir
set MSVCDir=%DevEnvDir%\..\..\VC7
goto VC7Detected

:ChkVC6_MsVCDir
IF "x%MSDevDir%x"=="xx" Goto DetectVC6

REM MSDevDir Exists. Can we derive MSVCDir from MSDevDir?
REM Check for VC6
IF NOT EXIST "%MSDevDir%\..\..\vc98\." Goto ChkVC5_MsVCDir
set MSVCDir=%MSDevDir%\..\..\vc98
goto VC6Detected

REM Check for VC5
:ChkVC5_MsVCDir
IF NOT EXIST "%MSDevDir%\..\VC\." Goto DetectVC6
set MSVCDir=%MSDevDir%\..\VC
SET MSVCVer=5.0
goto Chk_OS

REM -------------------------------------------------------------------
:NotMsDevDirExists
REM -------------------------------------------------------------------
REM MSDevDir does not exist, does MSVCDir Exist?
if NOT "x%DevEnvDir%x" == "xx" Goto VC7Detected
IF "x%MSVCDir%x"=="xx" Goto DetectVC6

REM MSVCDir Exists. Can we derive MSDevDir from MSVCDir?
REM Check for VC6
IF NOT EXIST "%MSVCDir%\..\Common\msdev98\." Goto ChkVC5_MSDevDir

set MSDevDir=%MSVCDir%\..\Common\msdev98
goto VC6Detected

REM Check for VC5
:ChkVC5_MSDevDir
IF NOT EXIST "%MSVCDir%\..\SharedIDE\." Goto DetectVC6
set MSDevDir=%MSVCDir%\..\SharedIDE
set MSVCVer=5.0
goto Chk_OS

REM -------------------------------------------------------------------
:NotMsVnetDevDirExists
REM -------------------------------------------------------------------
REM MSDevDir does not exist, does MSVCDir Exist?
IF "x%MSVCDir%x"=="xx" Goto DetectVC6

If NOT "x%MSDevDir%x" == "xx" Goto VC6Detected

REM MSVCDir Exists. Can we derive DevEnvDir from it?
IF NOT EXIST "%MSVCDir%\..\Common7\." Goto NotMsDevDirExists

set DevEnvDir=%MSVCDir%\..\Common7\IDE
goto VC7Detected

:VC6Detected
set MSVCVer=6.0
goto Chk_OS

:VC7Detected
set MSVCVer=7.0
goto Chk_OS

REM -------------------------------------------------------------------
REM Set RETAIL
REM -------------------------------------------------------------------
:set_RETAIL
set NODEBUG=1
set DEBUGMSG=RETAIL
goto Done_Retail


REM -------------------------------------------------------------------
REM Set DEBUG
REM -------------------------------------------------------------------
:set_DEBUG
set NODEBUG=
set DEBUGMSG=DEBUG
goto Done_Debug


REM -------------------------------------------------------------------
:DetectVC6
REM -------------------------------------------------------------------
Echo.
Echo Attempting to detect a Microsoft Visual Studio installation
Echo.
Call "%MSSDK%\setup\VCDetect.exe" "%TEMP%\VCInit.bat"
IF NOT EXIST "%TEMP%\VCInit.bat" goto ErrorVCEnv
Call "%TEMP%\VCInit.bat"
Echo.
goto Chk_OS


REM -------------------------------------------------------------------
:ErrorVCEnv
REM -------------------------------------------------------------------
Echo.
Echo Warning: The environmental variables MSDevDir and MSVCDir
Echo  were not found to exist. Check your Lib, Include and PATH to
Echo  verify that the SDK Lib, Include, and Bin directories precede
Echo  the compiler directories in the environment.
Echo.
Echo Note: Microsoft Visual Studio provides VCVARS32.BAT to Set them.
Echo  You must run VCVARS32.BAT first and then run SETENV.BAT.
Echo.
Echo Current settings:
Echo Lib=%Lib%
Echo Include=%Include%
Echo PATH=%PATH%
Echo.
Goto Finish

REM -------------------------------------------------------------------
:ErrorBadPath
REM -------------------------------------------------------------------
Echo.
Echo Error: The file "%MSSdk%\setenv.bat" does not appear to exist, or
Echo        an existing MSSdk env. variable does not match the expected
Echo        value encoded in this batch file by Platform SDK Setup.
Echo        Please check the path and an existing MSSdk variable
Echo        for correctness.
Echo.
Goto Finish

REM -------------------------------------------------------------------
:ErrorUsage9x_IA64
REM -------------------------------------------------------------------
echo.
echo Building Samples for the IA64 Platform is not currently supported on 
echo Windows 95, 98, Millennium or NT 4.0 Platforms.
echo.

REM -------------------------------------------------------------------
:ErrorUsage9x
REM -------------------------------------------------------------------
echo  "Usage Setenv [/2000 | /XP32 | /SRV32] [/DEBUG | /RETAIL]"
echo.
echo                 /2000 - target Windows 2000 and IE 5.0
echo                 /XP32 (default) - target Windows XP 32
echo                 /SRV32 - target Windows Server 2003
echo                 /DEBUG - set the environment to DEBUG
echo                 /RETAIL - set the environment to RETAIL
Goto Finish

REM -------------------------------------------------------------------
:ErrorUsage
REM -------------------------------------------------------------------
echo  "Usage Setenv [/2000 | /XP32 | /XP64 | /SRV32 | /SRV64 | /x86_64] [/DEBUG | /RETAIL]"
echo.
echo                 /2000 - target Windows 2000 and IE 5.0
echo                 /XP32 (default) - target Windows XP 32
echo                 /XP64 - target Windows XP 64
echo                 /SRV32 - target Windows Server 2003 32 bit
echo                 /SRV64 - target Windows Server 2003 64 bit
echo                 /x86_64 - target Windoes for the x86_64 bit prerelease content
echo                 /DEBUG - set the environment to DEBUG
echo                 /RETAIL - set the environment to RETAIL
Goto Finish


REM -------------------------------------------------------------------
:end
IF "x%OS%x" == "xWindows_NTx" Goto end_NT
echo *** WARNING ***
echo You are currently building on a Windows 9x based platform.  Most samples have 
echo NMAKE create a destination directory for created objects and executables.  
echo There is a known issue with the OS where NMAKE fails to create this destination
echo directory when the current directory is several directories deep.  To fix this 
echo problem, you must create the destination directory by hand from the command 
echo line before calling NMAKE. 
echo.

:end_NT
set DEBUGMSG=
REM -------------------------------------------------------------------
